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
      // 과거 glob 10 경로가 남은 경우 기존 호환성 검사도 유지한다.
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
    const modules = lockedModules('glob');
    assert.ok(modules.length > 0);
    for (const directory of modules) {
      const { glob } = require(directory);
      const options = { cwd: root, windowsPathsNoEscape: true, nodir: true };
      assert.ok(glob.sync('src/**/*.ts', options).includes('src/app.ts'));
      assert.ok(glob.sync('src/{app,missing}.ts', options).includes('src/app.ts'));
      assert.deepEqual(glob.sync('src/__missing__/**/*.ts', options), []);
      assert.ok(glob.sync('src/**/*.ts', { ...options, absolute: true }).includes(path.join(root, 'src/app.ts')));
      // glob 10에만 필요했던 반환 API와 전처리 의미를 강제 교체하지 않는다.
      if (require(path.join(directory, 'package.json')).version.startsWith('10.')) {
        const minimatch = createRequire(path.join(directory, 'package.json'))('minimatch');
        const pattern = Array(7).fill('**/../a/b').join('/');
        const file = Array(7).fill('x/a/b').join('/');
        assert.equal(new minimatch.Minimatch(pattern, { optimizationLevel: 2 }).match(file), true);
      }
    }
    const match = require(path.join(root, 'node_modules/nodemon/lib/monitor/match'));
    const rules = [path.join(root, 'src/**/*'), `!${path.join(root, 'src/ignored/**')}`];
    const result = match(['src/app.ts', 'src/ignored/skip.ts', 'src/style.css'], rules, 'ts');
    assert.deepEqual(result.result, [path.join(root, 'src/app.ts')]);
  });

  test('coverage 소비자의 include/exclude와 동기·비동기 파일 검색을 유지한다', async () => {
    const plugins = lockedModules('babel-plugin-istanbul');
    assert.ok(plugins.length > 0);
    const fixture = fs.mkdtempSync(path.join(root, '.dependency-compat-'));
    const files = ['src/app.ts', 'src/nested/with space.ts', 'src/nested/한글.ts',
      'src/route.test.ts', 'src/ignored/skip.ts', 'src/style.css', 'node_modules/dependency/index.ts'];
    try {
      for (const file of files) {
        fs.mkdirSync(path.dirname(path.join(fixture, file)), { recursive: true });
        fs.writeFileSync(path.join(fixture, file), '');
      }
      const expected = files.slice(0, 3).sort();
      for (const directory of plugins) {
        const TestExclude = createRequire(path.join(directory, 'package.json'))('test-exclude');
        const filter = new TestExclude({ cwd: fixture, include: ['src/**/*.{ts,js}'],
          exclude: ['**/*.test.ts', '**/ignored/**'], extension: ['.ts'] });
        for (const file of files) {
          assert.equal(filter.shouldInstrument(path.join(fixture, file)), expected.includes(file), file);
        }
        const normalize = items => items.map(item => item.split(path.sep).join('/')).sort();
        assert.deepEqual(normalize(filter.globSync()), expected);
        assert.deepEqual(normalize(await filter.glob()), expected);
      }
    } finally {
      fs.rmSync(fixture, { recursive: true, force: true });
    }
  });

  test('glob 취소 후 하위 디렉터리 I/O를 계속하지 않는다', async () => {
    const fixture = fs.mkdtempSync(path.join(root, '.dependency-compat-'));
    try {
      for (const branch of ['one', 'two', 'three']) {
        fs.mkdirSync(path.join(fixture, branch, 'nested'), { recursive: true });
        fs.writeFileSync(path.join(fixture, branch, 'nested', 'sample.ts'), '');
      }
      for (const directory of lockedModules('glob')) {
        const { glob } = require(directory);
        const controller = new AbortController();
        const reason = new Error('dependency compatibility abort');
        let reads = 0;
        let readsAfterAbort = 0;
        const filesystem = { ...fs, readdir(directory, options, callback) {
          reads++;
          if (controller.signal.aborted) {
            readsAfterAbort++;
            queueMicrotask(() => callback(null, []));
            return;
          }
          fs.readdir(directory, options, (error, entries) => {
            controller.abort(reason);
            callback(error, entries);
          });
        } };
        await assert.rejects(glob('**/*.ts', { cwd: fixture, fs: filesystem, signal: controller.signal }),
          error => error === reason);
        await new Promise(resolve => setImmediate(resolve));
        assert.ok(reads > 0);
        assert.equal(readsAfterAbort, 0);
      }
    } finally {
      fs.rmSync(fixture, { recursive: true, force: true });
    }
  });
}

if (root.endsWith(`${path.sep}hello_ts`)) {
  test('ESLint flat config의 TypeScript 검사와 리터럴 타입 예제를 유지한다', async () => {
    const { ESLint } = require(path.join(root, 'node_modules/eslint'));
    const eslint = new ESLint({ cwd: root });
    const results = await eslint.lintFiles(['index.ts']);
    assert.equal(results.reduce((count, result) => count + result.errorCount, 0), 0);
    const [invalid] = await eslint.lintText('const unused: number = 1;', { filePath: 'lint-fixture.ts' });
    assert.ok(invalid.messages.some(message => message.ruleId === '@typescript-eslint/no-unused-vars'));
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
