import * as vscode from 'vscode';
import { ActivateExtension } from './activate_extension';

export function activate(context: vscode.ExtensionContext) {
    new ActivateExtension(context);
}

export function deactivate() {}