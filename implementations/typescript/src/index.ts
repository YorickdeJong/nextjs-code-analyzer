
import * as path from 'path';
import { CodeAnalyzer } from './code_analyser'

const basePath = process.cwd();
const addonPath = path.join(basePath, '..', '..', '..', 'cpp', 'build', 'Release', 'NextJS_Analyser.node');
const analyser = new CodeAnalyzer(addonPath);
const filePath = path.join(__dirname, '..', 'tests', 'test_data.js');

try {
    analyser.analysisFile(filePath);
    console.log(analyser.getTokens())
} catch (error) {
    console.error('Error:', error);
    process.exit(1);
}