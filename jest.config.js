/** @type {import('ts-jest').JestConfigWithTsJest} */
module.exports = {
  preset: 'ts-jest',
  testEnvironment: 'node',
  modulePathIgnorePatterns: ["<rootDir>/implementations/typescript/src/package.json", ],
  testPathIgnorePatterns: [
    "<rootDir>/implementations/typescript/nextjs-code-analyzer-extension/"
  ]
};