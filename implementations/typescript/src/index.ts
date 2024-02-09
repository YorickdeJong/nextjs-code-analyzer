
import * as path from 'path';
import { CodeAnalyzer } from './code_analyser'

const basePath = process.cwd();
const addonPath = path.join(basePath, 'implementations', 'cpp', 'build', 'Release', 'NextJS_Analyser.node');
const analyser = new CodeAnalyzer(addonPath);
const filePath = path.join(__dirname, '..', 'tests', 'test.js');

try {
    analyser.analysisFile(filePath);
} catch (error) {
    console.error('Error:', error);
    process.exit(1);
}