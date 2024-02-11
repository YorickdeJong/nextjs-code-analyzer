
import * as path from 'path';
import { CodeAnalyzer } from './code_analyser'

const basePath = process.cwd();
const addonPath = path.join(basePath, 'implementations', 'typescript', 'nextjs-code-analyzer-extension', 'out', 'cpp_build', 'NextJS_Analyser.node');
const analyser = new CodeAnalyzer(addonPath);
const filePath = path.join(__dirname, 'test_data', 'test_data_3.js');

try {
    console.time("Analysis Time"); 
    analyser.analysisFile(filePath);
    console.timeEnd("Analysis Time"); 
} catch (error) {
    console.error('Error: ', error);
    process.exit(1);
}