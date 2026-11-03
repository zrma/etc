# 의존성 보안 검사와 잔여 권고 판정

검토일: 2026-11-04. 이 문서는 알려진 의존성 권고와 현재 예제의 사용 조건을
기록한다. 전체 소스 코드 보안 감사나 향후 입력 경로에 대한 보증은 아니다.

## 검사 범위와 실행

```sh
node --test scripts/audit-dependencies.test.cjs
node scripts/audit-dependencies.cjs
cd RabbitMQPractice/pkg/mq
GOTOOLCHAIN=go1.26.10 govulncheck -scan=module
# SkaffoldPractice에서도 같은 명령을 실행한다.
```

Node 검사는 `security/dependency-policy.json`에 나열된 pnpm 프로젝트 6개의
runtime/dev 전체 lockfile을 registry의 최신 권고와 대조한다. 새 pnpm lockfile이
추가되거나 기존 검사 대상이 누락되면 coverage 검사에서 실패한다.
Go 검사는 RabbitMQ와 Skaffold 두 모듈의 dependency와 Go 표준 라이브러리를 검사한다.
로컬에서 CI와 같은 SDK를 검사하려면 `GOTOOLCHAIN=go1.26.10`을 설정한다.
다른 언어의 과거 학습 예제, lockfile이 없는 예제와 배포 상태는 이 gate의 범위가 아니다.

공개 저장소의 `Dependency security` CI는 관련 manifest, lockfile, 정책 또는 검사
코드 변경과 매주 정기 실행에서 검사한다. 정기 실행은 소스가 바뀌지 않아도 새로
공개된 권고를 탐지한다. job은 공개 저장소에서만 실행한다. 로컬에서도 같은 명령을
사용할 수 있으며, 취약점을 자동 수정하거나 알림을 dismiss하지 않는다.

## 실패 조건과 예외

새 GHSA, 패키지, 버전, 심각도 또는 직접 의존 경로가 등장하면 실패한다.
조회 오류, 잘못된 응답, 누락된 결과와 만료된 활성 예외도 성공으로 처리하지 않는다.
낮은 심각도의 신규 권고도 판정 대상이다.

예외는 GHSA + 프로젝트 + 정확한 버전 + 심각도 + 소비 경로에 한정한다.
검토일, 사유, 공식 근거, 재검토 조건과 최대 31일의 만료일을 필수로 둔다.
현재 예외 만료일은 2026-12-03이다. 버전 범위나 전체 패키지 무시 규칙은 사용하지 않는다.

새 권고가 발견되면 입력 경로와 호출 옵션, 유지해야 할 정상 동작을 먼저 확인한다.
호환 가능한 수정은 재현과 정상 대조 검사를 거쳐 적용하고, 예외가 필요하면 근거와
재검토 조건을 갱신한다. 만료일만 자동 연장하지 않는다.

## 판정 기록

| 대상 | 현재 판정 | 근거와 재검토 조건 |
|---|---|---|
| CRA의 SVGO 권고 3건 | 의존 경로 제거 | CRA/SVGR/webpack을 Vite로 교체해 SVGO 1이 lockfile에서 제거됐다. 과거에는 `svgo:false`와 저장소 SVG만 사용하는 조건에서 비노출로 판정했다. 외부 SVG 정화 기능을 추가하면 전용 검증이 필요하다. |
| CRA의 deepmerge 및 minimatch 권고 | 의존 경로 제거 | `react-scripts`와 `eslint-config-react-app`을 제거했다. 구 도구 체인의 강제 major override를 남기지 않았다. |
| `GHSA-g3hv-75wg-m249`, minimatch 3.1.5 | Next 예제의 영향 구현 없음 | 3 계열에는 해당 `firstPhasePreProcess` 구현이 없다. Next lint 플러그인의 callable CommonJS 소비자를 유지한다. TypeScript 예제는 ESLint 10, Supabase 예제는 Jest 30.5로 이 경로를 제거했다. 새 버전·소비자 또는 공식 영향 코드 설명이 바뀌면 재검토한다. |
| 같은 GHSA, minimatch 9.0.9 | 의존 경로 제거 | Jest 30.5.2와 coverage 소비자의 test-exclude 8을 사용하고 glob 14.0.3을 적용한다. Supabase lockfile에는 minimatch 11.0.4만 남는다. |
| `GHSA-gcqx-w48m-w2h4`, deepmerge 4.3.1 | CVE 철회 | 발급 기관이 `CVE-2026-93753`을 REJECTED 처리했다. 남은 소비자는 Jest 설정 병합이다. 공식 판정이나 소비 경로 변경 시 재검토한다. |
| `GHSA-3g3m-2fjr-6pw4`, glob 10.5.0 / 13.0.6 | 수정 완료 | Supabase 예제의 Jest 및 coverage 경로를 수정판 glob 14.0.3으로 옮겼다. 취소 후 추가 디렉터리 읽기 검사에서 구 13.0.6은 실패하고 14.0.3은 통과한다. |
| qs 6.15.2 | 수정 완료 | practice 예제에서 6.16.1로 교체했다. 비호출 `toString`의 comma 직렬화 재현, 정상 HTTP query/form 대조와 타입 검사를 통과했다. |

minimatch 10 소비자는 11.0.4로 갱신했다. 제거된 경로의 예외 4개도 삭제했다.
현재 예외는 Next 예제의 minimatch 3과 철회된 deepmerge CVE에 대한 2개다.

## Dependabot 해석 실패와 호환성

Dependabot의 Supabase 보안 업데이트는 가장 최근에 해석 가능한 minimatch가
3.1.5이고 권고의 수정 버전은 11.0.1이라는 이유로 실패했다. Jest를 같은 major의
30.5.2로 갱신해 상위 도구가 정식으로 채택한 glob 13 소비 API로 옮긴다.
coverage의 `babel-plugin-istanbul@8.0.0`에만 `test-exclude` 8.0.0 override를 둔다.
이 릴리스는 기존 class / include / exclude / 동기·비동기 검색 API를 유지하고,
glob 갱신과 Node 20 이상 요구를 포함한다. CI는 Node 24를 사용한다.
glob 13의 AbortSignal 권고도 해결하도록 이 소비 경로에는 glob 14.0.3을 적용한다.
이 경로의 matcher는 minimatch 11을 사용한다.

구 glob 10에 minimatch 11을 직접 연결하는 방식에서 발견했던 복합 `**/..`
패턴 회귀는 구 소비자를 교체하는 판단의 근거로 보존한다. 현재 소비자의 정상
패턴은 globstar / brace / 없는 파일 / 절대 경로, coverage의 include / exclude /
공백·한글 경로 / node_modules 제외와 동기·비동기 결과를 검사한다.
기존 Jest / ts-jest 테스트 4개와 coverage 실행 방식도 유지한다.
Jest의 native 파일 감시 의존성인 `@parcel/watcher`를 build script 허용 목록에
추가하고, CI와 같은 일반 frozen install에서도 검사한다.
서버 진입점의 누락된 body-parser 타입 선언도 직접 개발 의존성으로 추가해
전체 TypeScript 검사를 CI에 연결한다.
TypeScript 예제는 ESLint 10의 flat config로 기존 권장 TypeScript 규칙과
Prettier 호환 설정을 옮겼다. 리터럴 타입·widening 학습 코드는 단일 행 예외로
의도를 명시하고 유지하며, 실제 lint와 타입 검사를 CI에 연결한다.

Next 예제의 React / import / 접근성 lint 플러그인은 여전히 minimatch 3을
callable CommonJS 함수로 사용한다. 이 경로의 major 강제 교체는 API 호환성을
깨뜨린다. deepmerge 4.3.1은 registry에 수정 버전이 없고 공식 CVE가 철회됐다.
따라서 이 두 알림은 버전 변경만으로 해결했다고 주장하지 않는다.
실제 의존성 수정으로 닫힌 알림과 upstream 영향 버전 판정이 필요한 알림을 구분한다.

패키지 관리자도 예제와 CI에서 pnpm 11.13.1로 맞춘다. 기존 11.12.0은 공식
registry에서 고장 난 릴리스로 폐기 처리하고 11.13.1 이상을 권장한다.
같은 major의 권장 최소 수정판을 사용하며, 최소 릴리스 경과 시간과
lockfile 공급망 검증 정책은 유지한다.

## Go 도구 체인 수정

새 CI의 모듈 수준 감사는 기존 Go 1.26.5 표준 라이브러리의 권고 22건을 탐지했다.
로컬의 더 최신 Go가 이를 가릴 수 있어, 두 go.mod의 최소 도구 체인을 같은
1.26 계열의 보안 수정판 1.26.10으로 올렸다. Skaffold Docker builder의 SDK도
같은 패치 버전으로 맞췄다. 검사 범위를 symbol 수준으로 낮추거나
Go 권고를 예외로 숨기지 않았다. CI는 각 go.mod의 도구 체인을 사용하며 로컬 대조도
같은 SDK를 강제한다. 모듈 수준 권고 수를 실제 호출 가능한 취약점 수로 해석하지 않는다.

## 공식 근거

- [minimatch 전처리 증폭](https://github.com/isaacs/minimatch/security/advisories/GHSA-g3hv-75wg-m249)
- [deepmerge CVE의 공식 철회 기록](https://github.com/CVEProject/cvelistV5/blob/main/cves/2026/93xxx/CVE-2026-93753.json)
- [glob AbortSignal 취소 우회](https://github.com/isaacs/node-glob/security/advisories/GHSA-3g3m-2fjr-6pw4)
- [SVGO namespace/URL 우회](https://github.com/svg/svgo/security/advisories/GHSA-w27v-7q3p-w38r)
- [SVGO foreignObject 우회](https://github.com/svg/svgo/security/advisories/GHSA-4vpr-x523-8j87)
- [SVGO script 제거 우회](https://github.com/svg/svgo/security/advisories/GHSA-2p49-hgcm-8545)
- [qs comma 직렬화 오류](https://github.com/ljharb/qs/security/advisories/GHSA-6pq8-jhm2-2vcw)

- [Go 보안 패치 릴리스 기록](https://go.dev/doc/devel/release#go1.26.0)
- [Jest 30 릴리스와 glob 13 전환](https://github.com/jestjs/jest/blob/main/CHANGELOG.md)
- [test-exclude 8 변경 기록](https://github.com/istanbuljs/test-exclude/blob/master/CHANGELOG.md)
- [ESLint 10 마이그레이션](https://eslint.org/docs/latest/use/migrate-to-10.0.0)
- [pnpm 11.12.0 공식 폐기 메타데이터](https://registry.npmjs.org/pnpm/11.12.0)
- [pnpm 11.13.1 릴리스](https://github.com/pnpm/pnpm/releases/tag/v11.13.1)
