import * as vscode from 'vscode';
import { CodeAnalyzer } from './code_analyzer';
import { DiagnosticManager } from './diagnostic_manager';

export class ActivateExtension {
    private codeAnalyzer: CodeAnalyzer;
    private diagnosticManager: DiagnosticManager;

    constructor(context: vscode.ExtensionContext) {
        this.codeAnalyzer = new CodeAnalyzer();
        this.diagnosticManager = new DiagnosticManager();

        this.registerEvents(context);
    }

    private registerEvents(context: vscode.ExtensionContext) {
        context.subscriptions.push(
            vscode.window.onDidChangeActiveTextEditor(editor => {
                if (editor) {
                    this.runAnalysis(editor);
                }
            }),
            vscode.workspace.onDidChangeTextDocument(event => {
                if (vscode.window.activeTextEditor && event.document === vscode.window.activeTextEditor.document) {
                    this.runAnalysis(vscode.window.activeTextEditor);
                }
            }),
            vscode.commands.registerCommand('nextjs-code-analyzer.nextjs', () => {
                const activeEditor = vscode.window.activeTextEditor;
                if (activeEditor) {
                    this.runAnalysis(activeEditor);
                }
            })
        );
    }

    private runAnalysis(editor: vscode.TextEditor) {
        const diagnostics = this.codeAnalyzer.analyzeCode(editor.document.getText());
        this.diagnosticManager.updateDiagnostics(editor.document, diagnostics);
    }
}