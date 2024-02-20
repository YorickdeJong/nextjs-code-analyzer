import * as vscode from 'vscode';
import * as babelParser from '@babel/parser';
import * as path from 'path';
import * as fs from 'fs';
import * as os from 'os';



class CodeAnalyzer {
    
    public constructor() {
      try {
          // Check if running in production environment
          if (process.env.NODE_ENV === 'production') {
            // In production, select the binary based on OS
            switch(os.platform()) {
                case 'win32':
                    this.addonPath = path.join(__dirname, 'cpp_build', 'NextJS_Analyser_windows.node');
                    break;
                case 'darwin':
                    this.addonPath = path.join(__dirname, 'cpp_build', 'NextJS_Analyser_macOs.node');
                    break;
                case 'linux':
                    this.addonPath = path.join(__dirname, 'cpp_build', 'NextJS_Analyser_ubuntu.node');
                    break;
                default:
                    throw new Error('Unsupported platform');
            }
          } else {
            // In development, use the generic path (assuming you're developing on one platform)
            this.addonPath = path.join(__dirname, 'cpp_build', 'NextJS_Analyser.node');
          }
    
          this.addon = require(this.addonPath);
      }
      catch (err) {
        console.log('err: ', err)
      }
    }
    public analyzeCode(code: string): vscode.Diagnostic[] {
        console.log('dir_name: ', this.addonPath)
        if (!fs.existsSync(this.addonPath)) {
          console.log('Addon file not found:', this.addonPath);
        }


        
        console.log(this.addon);
        const ast = this.passSourceCode(code)
        
        const astJson = JSON.stringify(ast, null, 2);
      
        // Get analysis results from your addon
        const analysisResults = this.addon.CreateReport(astJson);
        console.log('analysisResult: ', analysisResults)
        return this.analysisReport(analysisResults)
    }

    private passSourceCode(code: string) {
        return babelParser.parse(code, {
            sourceType: "module",
            plugins: [
              "jsx",
              "typescript", 
            ],
            errorRecovery: true,
            ranges: true,
            tokens: true
        });
    }

    private analysisReport (analysisResults : any): vscode.Diagnostic[]{
        return analysisResults.tokens.map((token: any) => {
            if (token.comment) {
              const startLine = token.loc.start.line - 1;
              const startChar = token.loc.start.column;
              const endLine = token.loc.end.line - 1;
              const endChar = token.loc.end.column;
        
              const range = new vscode.Range(
                new vscode.Position(startLine, startChar),
                new vscode.Position(endLine, endChar)
              );
        
              return new vscode.Diagnostic(
                range,
                token.comment.value,
                vscode.DiagnosticSeverity.Warning 
              );
            }
          }).filter((diagnostic: vscode.Diagnostic | undefined) => diagnostic !== undefined);
        
        
    }
    private addon: any
    private addonPath: any
    
}


export {CodeAnalyzer}