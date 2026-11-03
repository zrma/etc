const assert = require('node:assert/strict');
const { test } = require('node:test');
const { evaluateAudit, validatePolicy } = require('./audit-dependencies.cjs');

const project = 'example';
const entry = {
  project, advisory: 'GHSA-aaaa-bbbb-cccc', package: 'example-dependency', severity: 'moderate',
  versions: ['1.2.3'], pathPrefixes: ['.>test-tool>'], reviewed: '2026-11-03', expires: '2026-12-03',
  reason: 'trusted test configuration', recheckWhen: 'a new caller is introduced',
  reference: 'https://example.com/advisory',
};
const policy = { schemaVersion: 1, projects: [project], exceptions: [entry] };
const counts = { info: 0, low: 0, moderate: 0, high: 0, critical: 0 };
function report(overrides = {}, finding = {}) {
  return {
    advisories: {
      known: {
        github_advisory_id: entry.advisory, module_name: entry.package, severity: 'moderate',
        findings: [{ version: '1.2.3', paths: ['.>test-tool>example-dependency'], ...finding }], ...overrides,
      },
    },
    metadata: { vulnerabilities: { ...counts, moderate: 1 } },
  };
}
const check = (input, selectedPolicy = policy, date = '2026-11-03') => evaluateAudit(project, input, selectedPolicy, date);

test('a reviewed advisory is limited to its exact package, version, severity and caller', () => {
  assert.equal(check(report()).allowed.length, 1);
  for (const input of [
    report({ github_advisory_id: 'GHSA-dddd-eeee-ffff' }),
    report({ module_name: 'different-dependency' }),
    report({ severity: 'critical' }),
    report({}, { version: '1.2.4' }),
    report({}, { paths: ['.>request-handler>example-dependency'] }),
    report({}, { paths: ['.>test-tool>example-dependency', '.>request-handler>example-dependency'] }),
  ]) assert.equal(check(input).blocked.length, 1);
});
test('new low-severity advisories also fail', () => {
  assert.equal(check(report({ severity: 'low', github_advisory_id: 'GHSA-dddd-eeee-ffff' })).blocked.length, 1);
});
test('expired and not-yet-reviewed exceptions cannot pass', () => {
  assert.equal(check(report(), policy, '2026-12-03').blocked.length, 1);
  assert.equal(check(report(), policy, '2026-11-02').blocked.length, 1);
});
test('network, schema and incomplete results fail closed', () => {
  for (const input of [{}, { error: 'registry unavailable' }, report({}, { paths: [] }),
    { advisories: {}, metadata: { vulnerabilities: { high: 1 } } }]) {
    assert.throws(() => check(input));
  }
});
test('an empty valid audit passes without blanket exceptions', () => {
  const result = check({ advisories: {}, metadata: { vulnerabilities: counts } });
  assert.deepEqual(result, { allowed: [], blocked: [] });
});
test('wildcards and long-lived exceptions are rejected', () => {
  for (const changed of [{ pathPrefixes: ['.>'] }, { versions: ['*'] }, { pathPrefixes: ['.>tool>*'] }, { expires: '2027-01-01' }]) {
    const candidate = { ...policy, exceptions: [{ ...entry, ...changed }] };
    assert.throws(() => validatePolicy(candidate));
  }
});
