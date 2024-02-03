"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const babelParser = __importStar(require("@babel/parser"));
const fs = __importStar(require("fs"));
const addon = require('./cpp/build/Release/NextJS_Analyser.node');
const filePath = process.argv[2] || '';
// Ensure the user provided a file path
if (!filePath) {
    console.error('Usage: node parse.js <path-to-source-file>');
    process.exit(1);
}
try {
    // Read the source file into an array of lines
    const sourceCode = fs.readFileSync(filePath, 'utf8');
    const lines = sourceCode.split('\n');
    // Parse the file
    const ast = babelParser.parse(sourceCode, {
        sourceType: "module",
        plugins: [
            "jsx",
            "typescript", // if you're parsing TypeScript
            // other plugins as needed
        ],
        errorRecovery: true,
        attachComment: true,
        ranges: true,
        tokens: true,
    });
    const astJson = JSON.stringify(ast, null, 2);
    // Get analysis results
    const analysisResults = addon.Analyzer(astJson);
    analysisResults.tokens.forEach((token) => {
        if (token.comment) {
            // Insert the comment into the source code
            // Assuming the 'line' in the comment is 1-based
            const lineIndex = token.loc.start.line - 1;
            if (lineIndex >= 0 && lineIndex < lines.length) {
                lines[lineIndex] += ` // ${token.comment.value}`;
            }
        }
    });
    // Write the modified lines back to a file (or to a new file)
    fs.writeFileSync(filePath, lines.join('\n'));
}
catch (error) {
    console.error('Error:', error);
}
