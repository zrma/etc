const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const { createRequire } = require('node:module');
const { test } = require('node:test');

const root = process.cwd();
const lock = fs.readFileSync(path.join(root, 'pnpm-lock.yaml'), 'utf8');
const store = path.join(root, 'node_modules/.pnpm');

// 재설치 후 남은 이전 디렉터리 대신 현재 lockfile의 패키지만 검증한다.
function lockedModules(name) {
  return fs.readdirSync(store)
    .filter(entry => entry.startsWith(`${name.replace('/', '+')}@`))
    .map(entry => path.join(store, entry, 'node_modules', name))
    .filter(directory => {
      const { version } = require(path.join(directory, 'package.json'));
      return lock.includes(`\n  ${name}@${version}:`)
        || lock.includes(`\n  '${name}@${version}'`)
        || lock.includes(`\n  '${name}@${version}(`);
    });
}

if (!root.endsWith(`${path.sep}practice`)) {
  test('glob 전처리 증폭을 제한하고 일반 파일 패턴을 유지한다', () => {
    const modules = lockedModules('minimatch');
    assert.ok(modules.length > 0);
    for (const directory of modules) {
      const { Minimatch } = require(directory);
      const { version } = require(path.join(directory, 'package.json'));
      // Jest 전용 glob 10의 minimatch 9는 별도 호환성 검사로 유지한다.
      if (!version.startsWith('9.')) {
        for (const count of [7, 9]) {
          const pattern = Array(count).fill('**/../a/b').join('/');
          const matcher = new Minimatch(pattern, { optimizationLevel: 2, braceExpandMax: 64 });
          assert.ok(matcher.set.length <= 64, `${directory}: ${matcher.set.length} patterns`);
        }
      }
      if (typeof Minimatch.prototype.firstPhasePreProcess === 'function') {
        const matcher = new Minimatch('**/../a/b/**/../c/d', { optimizationLevel: 2 });
        assert.equal(matcher.match('../a/b/../c/d'), true);
        assert.equal(matcher.match('x/a/b/y/c/d'), true);
      }
      assert.equal(new Minimatch('**/*.ts').match('src/main.ts'), true);
      assert.equal(new Minimatch('**/*.ts').match('src/main.js'), false);
    }
  });
}

if (root.endsWith(`${path.sep}practice`)) {
  test('qs comma 입력의 비호출 toString과 정상 query/form을 처리한다', async () => {
    const request = require(path.join(root, 'node_modules/supertest'));
    const agentRequire = createRequire(require.resolve('superagent', { paths: [require.resolve(path.join(root, 'node_modules/supertest'))] }));
    const qs = agentRequire('qs');
    for (const encodeValuesOnly of [false, true]) {
      for (const toString of ['x', null, {}]) {
        for (const item of [{ toString }, Object.assign(Object.create(null), { toString })]) {
          assert.doesNotThrow(() => qs.stringify({ a: [item] }, { arrayFormat: 'comma', encodeValuesOnly }));
        }
      }
      assert.equal(qs.stringify({ a: ['one', 'two'] }, { arrayFormat: 'comma', encodeValuesOnly }),
        encodeValuesOnly ? 'a=one,two' : 'a=one%2Ctwo');
    }
    const agent = agentRequire('superagent');
    assert.equal(agent.serialize['application/x-www-form-urlencoded']({ a: ['one', 'two'], blank: null }), 'a=one&a=two&blank');
    const app = (req, res) => {
      let body = '';
      req.on('data', chunk => { body += chunk; });
      req.on('end', () => {
        res.setHeader('Content-Type', 'application/json');
        res.end(JSON.stringify({ url: req.url, body }));
      });
    };
    const query = await request(app).get('/').query({ a: ['one', 'two'] }).expect(200);
    assert.equal(query.body.url, '/?a=one&a=two');
    const form = await request(app).post('/').type('form').send({ a: ['one', 'two'], blank: null }).expect(200);
    assert.equal(form.body.body, 'a=one&a=two&blank');
  });
}

if (root.endsWith(`${path.sep}supabase`)) {
  test('Jest의 glob.sync 소비 API와 nodemon 필터를 유지한다', () => {
    const modules = lockedModules('glob').filter(directory => require(path.join(directory, 'package.json')).version.startsWith('10.'));
    assert.ok(modules.length > 0);
    for (const directory of modules) {
      const { glob } = require(directory);
      const options = { cwd: root, windowsPathsNoEscape: true, nodir: true };
      assert.ok(glob.sync('src/**/*.ts', options).includes('src/app.ts'));
      assert.ok(glob.sync('src/{app,missing}.ts', options).includes('src/app.ts'));
      assert.deepEqual(glob.sync('src/__missing__/**/*.ts', options), []);
      assert.ok(glob.sync('src/**/*.ts', { ...options, absolute: true }).includes(path.join(root, 'src/app.ts')));
      const minimatch = createRequire(path.join(directory, 'package.json'))('minimatch');
      const pattern = Array(7).fill('**/../a/b').join('/');
      const file = Array(7).fill('x/a/b').join('/');
      assert.equal(new minimatch.Minimatch(pattern, { optimizationLevel: 2 }).match(file), true);
    }
    const match = require(path.join(root, 'node_modules/nodemon/lib/monitor/match'));
    const rules = [path.join(root, 'src/**/*'), `!${path.join(root, 'src/ignored/**')}`];
    const result = match(['src/app.ts', 'src/ignored/skip.ts', 'src/style.css'], rules, 'ts');
    assert.deepEqual(result.result, [path.join(root, 'src/app.ts')]);
  });
}

const parsers = lockedModules('@typescript-eslint/parser');
if (parsers.length) {
  test('typed parser의 allowDefaultProject 패턴을 유지한다', () => {
    const fixture = fs.mkdtempSync(path.join(root, '.dependency-compat-'));
    const parser = createRequire(path.join(parsers[0], 'package.json'))('@typescript-eslint/parser');
    try {
      fs.writeFileSync(path.join(fixture, 'tsconfig.json'), JSON.stringify({ compilerOptions: { allowJs: true }, include: ['included.ts'] }));
      fs.writeFileSync(path.join(fixture, 'included.ts'), 'export const value = 1;');
      fs.writeFileSync(path.join(fixture, 'allowed.js'), 'const value = 1;');
      const options = { tsconfigRootDir: fixture, projectService: { allowDefaultProject: ['allowed.js'] } };
      const result = parser.parseForESLint('const value = 1;', { ...options, filePath: path.join(fixture, 'allowed.js') });
      assert.ok(result.services.program);
      assert.throws(() => parser.parseForESLint('const value = 1;', { ...options, filePath: path.join(fixture, 'blocked.js') }), /project service|allowDefaultProject/);
    } finally {
      parser.clearCaches();
      fs.rmSync(fixture, { recursive: true, force: true });
    }
  });
}
