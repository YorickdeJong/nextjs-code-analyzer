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
            })
        );
        
        context.subscriptions.push(vscode.workspace.onDidChangeTextDocument(event => {
                if (vscode.window.activeTextEditor && event.document === vscode.window.activeTextEditor.document) {
                    this.runAnalysis(vscode.window.activeTextEditor);
                }
            }),
        );
        
        context.subscriptions.push(vscode.commands.registerCommand('nextjs-code-analyzer.toggleIgnoreWarnings', () => {
            console.log('Toggle command executed');
            this.toggleIgnoreWarnings();
        }));
        
        context.subscriptions.push(vscode.commands.registerCommand('nextjs-code-analyzer.nextjs', () => {
                const activeEditor = vscode.window.activeTextEditor;
                if (activeEditor) {
                    console.log('NextJs is active')    
                    this.runAnalysis(activeEditor, true);
                }
            })
        );


          
    }

    private runAnalysis(editor: vscode.TextEditor, fromNextJsCommand = false) {
        // // Temporarily override the ignoreWarnings setting for this analysis
        const diagnostics = this.codeAnalyzer.analyzeCode(editor.document.getText());
        this.diagnosticManager.updateDiagnostics(editor.document, diagnostics, fromNextJsCommand);
    

    }

    private toggleIgnoreWarnings() {
        const config = vscode.workspace.getConfiguration();
        const currentSetting = config.get<boolean>('nextjsCodeAnalyzer.ignoreWarnings', false);
        config.update('nextjsCodeAnalyzer.ignoreWarnings', !currentSetting, vscode.ConfigurationTarget.Global);
    
        if (currentSetting) {
            // Re-run analysis if we are turning warnings back on
            const activeEditor = vscode.window.activeTextEditor;
            if (activeEditor) {
                this.runAnalysis(activeEditor);
            }
        } else {
            // Clear diagnostics if we are turning warnings off
            this.diagnosticManager.clearDiagnostics();
        }
    }
}