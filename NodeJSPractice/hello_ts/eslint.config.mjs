import tsPlugin from "@typescript-eslint/eslint-plugin";
import prettier from "eslint-config-prettier/flat";

export default [...tsPlugin.configs["flat/recommended"], prettier];
