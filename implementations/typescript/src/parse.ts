import * as babelParser from '@babel/parser';
import * as fs from 'fs';
const path = require('path');
const addonPath = path.join(process.cwd(), 'implementations', 'cpp', 'build', 'Release', 'NextJS_Analyser.node');
const addon = require(addonPath);

  
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
    ],
    errorRecovery: true,
    attachComment: true,
    ranges: true,
    tokens: true,}
  );
  const astJson = JSON.stringify(ast, null, 2);

  console.log('ast', astJson)
  // Get analysis results
  const analysisResults = addon.Analyzer(astJson);

  analysisResults.tokens.forEach((token: any) => {
    if (token.comment) {
      console.log("token", token.comment)
      // // Insert the comment into the source code
      // // Assuming the 'line' in the comment is 1-based
      // const lineIndex = token.loc.start.line -1;
      // if (lineIndex >= 0 && lineIndex < lines.length) {
      //   lines[lineIndex] += ` // ${token.comment.value}`;
      // }
    }
  });

  
  // Write the modified lines back to a file (or to a new file)
  fs.writeFileSync(filePath, lines.join('\n'));
} catch (error) {
  console.error('Error:', error);
}