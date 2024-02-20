import * as babelParser from '@babel/parser';
import * as path from 'path'
import * as fs from 'fs'
import * as os from 'os';

const basePath = process.cwd();

class CodeAnalyzer {

  constructor() {
    if (process.env.NODE_ENV === 'production') {

      switch(os.platform()) {
          case 'win32':
              this.addonPath = path.join(basePath, 'implementations', 'typescript', 'nextjs-code-analyzer-extension', 'out', 'cpp_build', 'NextJS_Analyser_windows.node');
              break;
          case 'darwin':
              this.addonPath = path.join(basePath, 'implementations', 'typescript', 'nextjs-code-analyzer-extension', 'out', 'cpp_build', 'NextJS_Analyser_macOs.node');
              break;
          case 'linux':
              this.addonPath = path.join(basePath, 'implementations', 'typescript', 'nextjs-code-analyzer-extension', 'out', 'cpp_build', 'NextJS_Analyser_ubuntu.node');
              break;
          default:
              throw new Error('Unsupported platform');
      }
    } else {
      // In development, use the generic path (assuming you're developing on one platform)
      this.addonPath = path.join(basePath, 'implementations', 'typescript', 'nextjs-code-analyzer-extension', 'out', 'cpp_build', 'NextJS_Analyser');
    }
    this.addon = require(this.addonPath);
    this.tokens = []
  }

  public analysisFile(filePath: string): void {
    if (!filePath) {
      throw new Error('File path must be provided!');
    }
    // Read the source file into an array of lines.
    const sourceCode = this.readFile(filePath);
  
    // Parse the file
    const ast = this.parseSourceCode(sourceCode)
    const astJson = JSON.stringify(ast, null, 2);
  
    this.analysisResults = this.addon.CreateReport(astJson);

    // Get analysis results

    this.analysisResults.tokens.forEach((token: any) => {
      if (token.comment) { 
          this.tokens.push(token);
      }
    });

  
    // Write the modified lines back to a file (or to a new file.
    this.writeFile(filePath, sourceCode);

  }

  public getTokens() {
    return this.tokens;
  }


  private addon: any
  private addonPath: string
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