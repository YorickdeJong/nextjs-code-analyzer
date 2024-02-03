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
const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
let astJson = '';
rl.question('Enter the path to your file: ', (filePath) => {
    // Read and parse the file
    try {
        const sourceCode = fs.readFileSync(filePath, 'utf8');
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
        astJson = JSON.stringify(ast, null, 2);
        addon.JsonReader(astJson);
    }
    catch (error) {
        console.error('Error reading file:', error);
    }
    rl.close();
});
