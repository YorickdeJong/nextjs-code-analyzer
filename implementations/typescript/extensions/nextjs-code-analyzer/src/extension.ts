import * as vscode from 'vscode';
import * as babelParser from '@babel/parser';
const path = require('path');
const addonPath = path.join(__dirname, '..', '..', '..', '..', '..', 'implementations', 'cpp', 'build', 'Release', 'NextJS_Analyser.node');
const addon = require(addonPath);


export function activate(context: vscode.ExtensionContext) {


	context.subscriptions.push(
		vscode.window.onDidChangeActiveTextEditor(editor => {
		if (editor) {
			const diagnostics = analyzeCode(editor.document.getText());
			updateDiagnostics(editor.document, diagnostics);
		}
		})
	);

	context.subscriptions.push(
		vscode.workspace.onDidChangeTextDocument(event => {
		if (vscode.window.activeTextEditor && event.document === vscode.window.activeTextEditor.document) {
			const diagnostics = analyzeCode(event.document.getText());
			updateDiagnostics(event.document, diagnostics);
		}
		})
	);

	let disposable = vscode.commands.registerCommand('nextjs-code-analyzer.nextjs', () => {
		// The command has been defined in the package.json file
		// Now provide the implementation of the command with registerCommand
		// The code you place here will be executed every time your command is executed
		const activeEditor = vscode.window.activeTextEditor;
		if (activeEditor) {
		const diagnostics = analyzeCode(activeEditor.document.getText());
		updateDiagnostics(activeEditor.document, diagnostics);
		}
		console.log('NextJS code analyzer is active!')
	});

	context.subscriptions.push(disposable);
}

function analyzeCode(code: string): vscode.Diagnostic[] {
    const ast = babelParser.parse(code, {
        sourceType: "module",
        plugins: [
          "jsx",
          "typescript", // if you're parsing TypeScript
          // other plugins as needed
        ],
        errorRecovery: true,
        attachComment: true,
        ranges: true,
        tokens: true
    });
    
    console.log(ast);
    // Clear existing comments in the AST before analysis
    ast.tokens && ast.tokens.forEach((token: any) => {
        if (token.comment) {
            console.log('check')
            delete token.comment;
        }
    });
  
    const astJson = JSON.stringify(ast, null, 2);

    // Get analysis results from your addon
    const analysisResults = addon.CreateReport(astJson);


    return analysisResults.tokens.map((token: any) => {
      if (token.comment) {
		    console.log(token.comment.value);

        // Assuming token.loc.start.line is 1-based
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
          vscode.DiagnosticSeverity.Warning // or appropriate severity
        );
      }
    }).filter((diagnostic: vscode.Diagnostic | undefined) => diagnostic !== undefined);
}


function updateDiagnostics(document: vscode.TextDocument, diagnostics: vscode.Diagnostic[]) {
    const diagnosticCollection = vscode.languages.createDiagnosticCollection('codeAnalyzer');
    diagnosticCollection.set(document.uri, diagnostics);
}




export function deactivate() {}