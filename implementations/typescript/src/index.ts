
import * as path from 'path';
import { CodeAnalyzer } from './code_analyser'


const analyser = new CodeAnalyzer();
const filePath = path.join(__dirname, '..', 'test_data', 'test_data_3.js');

try {
    console.time("Analysis Time"); 
    analyser.analysisFile(filePath);
    console.timeEnd("Analysis Time"); 
} catch (error) {
    console.error('Error: ', error);
    process.exit(1);
}