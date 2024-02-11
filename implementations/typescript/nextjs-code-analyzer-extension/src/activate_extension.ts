import * as vscode from 'vscode';
import { CodeAnalyzer } from './code_analyzer';
import { DiagnosticManager } from './diagnostic_manager';
import * as path from 'path';
import { existsSync } from 'fs';

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
    
        
        context.subscriptions.push(vscode.commands.registerCommand('nextjsCodeAnalyzer.nextjs', () => {
            // check if workspace nextjs project    
            if (this.detectNextJsProject()){
                    console.log('Nextjs project detected')

                    const config = vscode.workspace.getConfiguration();
                    const currentSetting = config.get<boolean>('nextjsCodeAnalyzer.ignoreWarnings', false);
                    config.update('nextjsCodeAnalyzer.ignoreWarnings', !currentSetting, vscode.ConfigurationTarget.Global);

                    // toggle warnings on or off
                    if (currentSetting) {
                        // Re-run analysis if we are turning warnings back on
                        const activeEditor = vscode.window.activeTextEditor;
                        if (activeEditor) {
                            this.runAnalysis(activeEditor, true);
                        }
                    } else {
                        // Clear diagnostics if we are turning warnings off
                        this.diagnosticManager.clearDiagnostics();
                    }
                }
                else {
                    console.log('Not a nextjs project')
                }               
            })
        );


          
    }

    private runAnalysis(editor: vscode.TextEditor, fromNextJsCommand = false) {
        // // Temporarily override the ignoreWarnings setting for this analysis
        const diagnostics = this.codeAnalyzer.analyzeCode(editor.document.getText());
        this.diagnosticManager.updateDiagnostics(editor.document, diagnostics, fromNextJsCommand);
    

    }

    private detectNextJsProject(): boolean {
        if (vscode.workspace.workspaceFolders) {
            const workspaceRoot = vscode.workspace.workspaceFolders[0].uri.fsPath;
            const nextConfigPathMjs = path.join(workspaceRoot, 'next.config.mjs');
            const nextConfigPathJs = path.join(workspaceRoot, 'next.config.js');
            // Check if either next.config.mjs or next.config.js exists
            return existsSync(nextConfigPathMjs) || existsSync(nextConfigPathJs);
        }
        return false; // No workspace folder is open, or neither config file exists
    }
    
}