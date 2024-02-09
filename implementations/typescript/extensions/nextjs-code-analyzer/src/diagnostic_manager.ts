import * as vscode from 'vscode';

export class DiagnosticManager {
    private diagnosticCollection: vscode.DiagnosticCollection;

    constructor() {
        this.diagnosticCollection = vscode.languages.createDiagnosticCollection('codeAnalyzer');
    }

    public updateDiagnostics(document: vscode.TextDocument, diagnostics: vscode.Diagnostic[]) {
        this.diagnosticCollection.set(document.uri, diagnostics);
    }
}