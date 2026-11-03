const fs = require('node:fs');
const path = require('node:path');
const { spawnSync } = require('node:child_process');

const repoRoot = path.resolve(__dirname, '..');
const severities = new Set(['info', 'low', 'moderate', 'high', 'critical']);

function validatePolicy(policy) {
  if (policy.schemaVersion !== 1 || !Array.isArray(policy.projects) || !Array.isArray(policy.exceptions)) {
    throw new Error('unsupported dependency policy');
  }
  if (!policy.projects.length || new Set(policy.projects).size !== policy.projects.length
    || policy.projects.some(project => typeof project !== 'string' || project.startsWith('/') || project.split('/').includes('..'))) {
    throw new Error('invalid project coverage');
  }
  for (const item of policy.exceptions) {
    const reviewed = Date.parse(item.reviewed + 'T00:00:00Z');
    const expires = Date.parse(item.expires + 'T00:00:00Z');
    if (!policy.projects.includes(item.project) || !/^GHSA-[a-z0-9]{4}-[a-z0-9]{4}-[a-z0-9]{4}$/.test(item.advisory)
      || typeof item.package !== 'string' || !severities.has(item.severity)
      || !Array.isArray(item.versions) || !item.versions.length || item.versions.some(version => !/^\d+\.\d+\.\d+$/.test(version))
      || !Array.isArray(item.pathPrefixes) || !item.pathPrefixes.length
      || item.pathPrefixes.some(prefix => typeof prefix !== 'string' || !/^\.>[^>*]+>/.test(prefix) || prefix.includes('*'))
      || !Number.isFinite(reviewed) || !Number.isFinite(expires) || expires <= reviewed || expires - reviewed > 31 * 86400000
      || !item.reason || !item.recheckWhen || !item.reference?.startsWith('https://')) {
      throw new Error('invalid or overly broad audit exception');
    }
  }
}

function evaluateAudit(project, report, policy, today = new Date().toISOString().slice(0, 10)) {
  validatePolicy(policy);
  if (!policy.projects.includes(project)) throw new Error('project is outside reviewed coverage');
  if (!report || report.error || !report.advisories || typeof report.advisories !== 'object'
    || Array.isArray(report.advisories) || !report.metadata?.vulnerabilities) {
    throw new Error('invalid registry audit response');
  }
  if ([...severities].some(level => !Number.isInteger(report.metadata.vulnerabilities[level])
    || report.metadata.vulnerabilities[level] < 0)) throw new Error('incomplete audit severity counts');
  const advisories = Object.values(report.advisories);
  if (!advisories.length && Object.values(report.metadata.vulnerabilities).some(count => count !== 0)) {
    throw new Error('audit response omitted reported advisories');
  }
  const allowed = [];
  const blocked = [];
  for (const advisory of advisories) {
    if (!advisory.module_name || !/^GHSA-[a-z0-9]{4}-[a-z0-9]{4}-[a-z0-9]{4}$/.test(advisory.github_advisory_id)
      || !severities.has(advisory.severity) || !Array.isArray(advisory.findings) || !advisory.findings.length) {
      throw new Error('unsupported advisory response');
    }
    for (const finding of advisory.findings) {
      if (!finding.version || !Array.isArray(finding.paths) || !finding.paths.length
        || finding.paths.some(route => typeof route !== 'string' || !route.startsWith('.>'))) {
        throw new Error('audit finding is missing its version or dependency route');
      }
      const exception = policy.exceptions.find(item => item.project === project
        && item.advisory === advisory.github_advisory_id && item.package === advisory.module_name
        && item.severity === advisory.severity && item.versions.includes(finding.version)
        && item.reviewed <= today && today < item.expires
        && finding.paths.every(route => item.pathPrefixes.some(prefix => route.startsWith(prefix))));
      const message = `${project}: ${advisory.github_advisory_id} ${advisory.module_name}@${finding.version}`;
      (exception ? allowed : blocked).push(message);
    }
  }
  return { allowed, blocked };
}

function lockProjects(directory = repoRoot) {
  const found = [];
  for (const entry of fs.readdirSync(directory, { withFileTypes: true })) {
    if (['.git', '.jj', 'node_modules', '.venv', 'target', 'build', '.next'].includes(entry.name)) continue;
    const filename = path.join(directory, entry.name);
    if (entry.isDirectory()) found.push(...lockProjects(filename));
    else if (entry.name === 'pnpm-lock.yaml') found.push(path.relative(repoRoot, directory).split(path.sep).join('/'));
  }
  return found.sort();
}

function main() {
  const policy = JSON.parse(fs.readFileSync(path.join(repoRoot, 'security/dependency-policy.json'), 'utf8'));
  validatePolicy(policy);
  if (JSON.stringify(lockProjects()) !== JSON.stringify([...policy.projects].sort())) {
    throw new Error('pnpm lockfile coverage changed; review security/dependency-policy.json');
  }
  let failures = 0;
  for (const project of policy.projects) {
    const result = spawnSync('pnpm', ['audit', '--json', '--audit-level', 'low'], {
      cwd: path.join(repoRoot, project), encoding: 'utf8', timeout: 120000, maxBuffer: 16 * 1024 * 1024,
    });
    if (result.error || result.signal || ![0, 1].includes(result.status)) throw new Error(`registry audit failed for ${project}`);
    const evaluated = evaluateAudit(project, JSON.parse(result.stdout), policy);
    if (result.status === 1 && !evaluated.allowed.length && !evaluated.blocked.length) {
      throw new Error(`registry audit failed without findings for ${project}`);
    }
    for (const message of evaluated.allowed) console.log(`REVIEWED ${message}`);
    for (const message of evaluated.blocked) console.error(`BLOCKED ${message}`);
    failures += evaluated.blocked.length;
    console.log(`${project}: ${evaluated.allowed.length} reviewed, ${evaluated.blocked.length} blocked`);
  }
  process.exitCode = failures ? 1 : 0;
}

module.exports = { evaluateAudit, validatePolicy };
if (require.main === module) {
  try { main(); } catch (error) { console.error(error.message); process.exitCode = 1; }
}
