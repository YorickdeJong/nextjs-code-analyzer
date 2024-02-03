import * as babelParser from '@babel/parser';
import * as fs from 'fs';
const addon = require('./cpp/build/Release/NextJS_Analyser.node');
const readline = require('readline');


const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
  });
  

let astJson = '';

rl.question('Enter the path to your file: ', (filePath : string) => {
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

  } catch (error) {
    console.error('Error reading file:', error);
  }

  rl.close();
});

