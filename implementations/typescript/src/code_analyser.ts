import * as babelParser from '@babel/parser';
const path = require('path');
const fs = require('fs');

class CodeAnalyzer {

  constructor(private addonPath: string) {
    this.addon = require(addonPath)
    this.tokens = []
  }

  public analysisFile(filePath: string): void {
    if (!filePath) {
      throw new Error('File path must be provided!');
    }
    // Read the source file into an array of lines
    const sourceCode = this.readFile(filePath);
  
    // Parse the file
    const ast = this.parseSourceCode(sourceCode)
    const astJson = JSON.stringify(ast, null, 2);

    const outputPath = path.join(__dirname, 'log.txt');

    // Write to the file synchronously
    fs.writeFileSync(outputPath, astJson);    
    this.analysisResults = this.addon.CreateReport(astJson);

    // Get analysis results

    this.analysisResults.tokens.forEach((token: any) => {
      if (token.comment) { 
          this.tokens.push(token);
      }
    });

  
    // Write the modified lines back to a file (or to a new file)
    this.writeFile(filePath, sourceCode);

  }

  public getTokens() {
    return this.tokens;
  }


  private addon: any
  private analysisResults: any
  private tokens: any[]

  private parseSourceCode(sourceCode: string) {
      return babelParser.parse(sourceCode, {
          sourceType: "module",
          plugins: ["jsx", "typescript"],
          errorRecovery: true,
          attachComment: true,
          ranges: true,
          tokens: true,
      });
    }

    private readFile(filePath: string): string {
      return fs.readFileSync(filePath, 'utf8');
    }

    private writeFile(filePath: string, content: string): void {
      fs.writeFileSync(filePath, content);
    }

}

export { CodeAnalyzer };