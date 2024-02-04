"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.deactivate = exports.activate = void 0;
const vscode = require("vscode");
const babelParser = require("@babel/parser");
const path = require('path');
const addonPath = path.join(__dirname, '..', '..', '..', '..', '..', 'implementations', 'cpp', 'build', 'Release', 'NextJS_Analyser.node');
const addon = require(addonPath);
function activate(context) {
    context.subscriptions.push(vscode.window.onDidChangeActiveTextEditor(editor => {
        if (editor) {
            const diagnostics = analyzeCode(editor.document.getText());
            updateDiagnostics(editor.document, diagnostics);
        }
    }));
    context.subscriptions.push(vscode.workspace.onDidChangeTextDocument(event => {
        if (vscode.window.activeTextEditor && event.document === vscode.window.activeTextEditor.document) {
            const diagnostics = analyzeCode(event.document.getText());
            updateDiagnostics(event.document, diagnostics);
        }
    }));
    let disposable = vscode.commands.registerCommand('nextjs-code-analyzer.nextjs', () => {
        // The command has been defined in the package.json file
        // Now provide the implementation of the command with registerCommand
        // The code you place here will be executed every time your command is executed
        const activeEditor = vscode.window.activeTextEditor;
        if (activeEditor) {
            const diagnostics = analyzeCode(activeEditor.document.getText());
            updateDiagnostics(activeEditor.document, diagnostics);
        }
        console.log('NextJS code analyzer is active!');
    });
    context.subscriptions.push(disposable);
}
exports.activate = activate;
function analyzeCode(code) {
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
    const astJson = JSON.stringify(ast, null, 2);
    console.log(astJson);
    // Get analysis results from your addon
    const analysisResults = addon.Analyzer(astJson);
    return analysisResults.tokens.map((token) => {
        if (token.comment) {
            console.log(token.comment.value);
            // Assuming token.loc.start.line is 1-based
            const startLine = token.loc.start.line - 1;
            const startChar = token.loc.start.column;
            const endLine = token.loc.end.line - 1;
            const endChar = token.loc.end.column;
            const range = new vscode.Range(new vscode.Position(startLine, startChar), new vscode.Position(endLine, endChar));
            return new vscode.Diagnostic(range, token.comment.value, vscode.DiagnosticSeverity.Warning // or appropriate severity
            );
        }
    }).filter((diagnostic) => diagnostic !== undefined);
}
function updateDiagnostics(document, diagnostics) {
    const diagnosticCollection = vscode.languages.createDiagnosticCollection('codeAnalyzer');
    diagnosticCollection.set(document.uri, diagnostics);
}
function deactivate() { }
exports.deactivate = deactivate;
//# sourceMappingURL=extension.js.map