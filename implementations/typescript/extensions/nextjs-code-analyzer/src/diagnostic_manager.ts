import * as vscode from 'vscode';

export class DiagnosticManager {
    private diagnosticCollection: vscode.DiagnosticCollection;

    constructor() {
        this.diagnosticCollection = vscode.languages.createDiagnosticCollection('codeAnalyzer');
    }

    updateDiagnostics(document: vscode.TextDocument, diagnostics: vscode.Diagnostic[], fromNextJsCommand: Boolean) {
        if (!fromNextJsCommand) {
            const ignoreWarnings = vscode.workspace.getConfiguration().get('nextjsCodeAnalyzer.ignoreWarnings', false);
            if (ignoreWarnings) {
                diagnostics = diagnostics.filter(diagnostic => diagnostic.severity !== vscode.DiagnosticSeverity.Warning);
            }
        }
        this.diagnosticCollection.set(document.uri, diagnostics);
    }

    clearDiagnostics() {
        this.diagnosticCollection.clear();
    }
}