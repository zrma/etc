# React 연습 앱

React 예제 화면을 Vite로 빌드하고 Vitest와 Testing Library로 검사한다.
기존 화면, 로고, manifest와 `build/` 출력 경로를 유지한다.

## 실행

Node.js 24.15 이상의 24 LTS 또는 26 이상과 package.json에 지정된 pnpm을 사용한다.

```sh
pnpm install --frozen-lockfile
pnpm start
pnpm check
pnpm preview
```

- `start` / `dev`: localhost:3000 개발 서버와 HMR.
- `lint`: 소스 정적 검사.
- `test`: Vitest 단일 실행. 대화형 실행은 `test:watch`.
- `build`: 배포 가능한 정적 파일을 `build/`에 생성. 상대 자산 경로를 사용한다.
- `preview`: 빌드 결과의 로컬 확인용 서버. 운영 서버로 사용하지 않는다.

서비스 워커는 기존처럼 등록하지 않는다. 기존 등록 해제 동작은 유지하며
이 예제는 오프라인 캐시나 외부 SVG 정화 기능을 제공하지 않는다.

CRA의 `eject`, `%PUBLIC_URL%`, `REACT_APP_*` 환경변수와 자동 webpack/Jest 설정은
사용하지 않는다. 새 클라이언트 환경변수가 필요하면 Vite의 `VITE_*` 및
`import.meta.env` 규칙을 사용하고, 비밀값을 번들에 포함하지 않는다.
