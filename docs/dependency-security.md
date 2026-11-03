# 의존성 보안 검사와 잔여 권고 판정

검토일: 2026-11-03. 이 문서는 알려진 의존성 권고와 현재 예제의 사용 조건을
기록한다. 전체 소스 코드 보안 감사나 향후 입력 경로에 대한 보증은 아니다.

## 검사 범위와 실행

```sh
node --test scripts/audit-dependencies.test.cjs
node scripts/audit-dependencies.cjs
cd RabbitMQPractice/pkg/mq
govulncheck -scan=module
```

Node 검사는 `security/dependency-policy.json`에 나열된 pnpm 프로젝트 6개의
runtime/dev 전체 lockfile을 registry의 최신 권고와 대조한다. 새 pnpm lockfile이
추가되거나 기존 검사 대상이 누락되면 coverage 검사에서 실패한다.
Go 검사는 RabbitMQ 모듈의 dependency와 Go 표준 라이브러리를 검사한다.
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
| `GHSA-g3hv-75wg-m249`, minimatch 3.1.5 | 영향 구현 없음 | 3 계열에는 해당 `firstPhasePreProcess` 구현이 없다. 기존 callable CommonJS 소비자를 유지한다. 새 버전·소비자 또는 공식 영향 코드 설명이 바뀌면 재검토한다. |
| 같은 GHSA, minimatch 9.0.9 | Jest 설정 경로로 제한 | 취약 전처리 구현 자체는 남는다. 요청 입력을 받지 않고 저장소 소유 Jest 설정만 처리한다. glob 10은 minimatch의 RegExp 반환 API를 요구한다. 최신 glob 동반 갱신은 복합 `**/..` 패턴이 상한에 도달할 때 정상 match가 false가 되는 회귀를 확인해 제외했다. 비신뢰 패턴 도입 또는 호환 가능한 upstream 수정 시 즉시 재검토한다. |
| `GHSA-gcqx-w48m-w2h4`, deepmerge 4.3.1 | CVE 철회 | 발급 기관이 `CVE-2026-93753`을 REJECTED 처리했다. 남은 소비자는 Jest 설정 병합이다. 공식 판정이나 소비 경로 변경 시 재검토한다. |
| `GHSA-3g3m-2fjr-6pw4`, glob 10.5.0 | 취소 경로 비노출 | registry 감사에서 추가 확인한 권고다. Jest의 직접 소비자는 signal 없는 `glob.sync`이며 비동기 `glob`/`globStream`의 AbortSignal 취소에 의존하지 않는다. 비동기·signal·외부 패턴 도입 시 재검토한다. |
| qs 6.15.2 | 수정 완료 | practice 예제에서 6.16.1로 교체했다. 비호출 `toString`의 comma 직렬화 재현, 정상 HTTP query/form 대조와 타입 검사를 통과했다. |

minimatch 10 소비자는 11.0.4로 갱신했다. Jest 전용 구버전의 상한 검사를
성공했다고 주장하지 않으며, `scripts/dependency-security.test.cjs`에서 별도
호환성 경계를 유지한다.

## 공식 근거

- [minimatch 전처리 증폭](https://github.com/isaacs/minimatch/security/advisories/GHSA-g3hv-75wg-m249)
- [deepmerge CVE의 공식 철회 기록](https://github.com/CVEProject/cvelistV5/blob/main/cves/2026/93xxx/CVE-2026-93753.json)
- [glob AbortSignal 취소 우회](https://github.com/isaacs/node-glob/security/advisories/GHSA-3g3m-2fjr-6pw4)
- [SVGO namespace/URL 우회](https://github.com/svg/svgo/security/advisories/GHSA-w27v-7q3p-w38r)
- [SVGO foreignObject 우회](https://github.com/svg/svgo/security/advisories/GHSA-4vpr-x523-8j87)
- [SVGO script 제거 우회](https://github.com/svg/svgo/security/advisories/GHSA-2p49-hgcm-8545)
- [qs comma 직렬화 오류](https://github.com/ljharb/qs/security/advisories/GHSA-6pq8-jhm2-2vcw)
