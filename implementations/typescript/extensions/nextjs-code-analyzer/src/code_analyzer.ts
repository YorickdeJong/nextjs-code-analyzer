import * as vscode from 'vscode';
import * as babelParser from '@babel/parser';
const path = require('path');


class CodeAnalyzer {
    
    public constructor() {
      this.addon = require(this.addonPath);
    }
    public analyzeCode(code: string): vscode.Diagnostic[] {
        const ast = this.passSourceCode(code)
        
        const astJson = JSON.stringify(ast, null, 2);
    
        // Get analysis results from your addon
        const analysisResults = this.addon.CreateReport(astJson);
    
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
    private addonPath = path.join(__dirname, '..', '..', '..', '..', '..', 'implementations', 'cpp', 'build', 'Release', 'NextJS_Analyser.node');
}


export {CodeAnalyzer}