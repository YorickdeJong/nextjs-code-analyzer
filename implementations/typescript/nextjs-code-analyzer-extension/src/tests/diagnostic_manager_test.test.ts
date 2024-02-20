jest.mock('vscode', () => ({
    languages: {
      createDiagnosticCollection: jest.fn(),
    },
  }), { virtual: true });

import * as vscode from 'vscode';
import { DiagnosticManager } from '../diagnostic_manager';



describe('DiagnosticManager Tests ', () => {
  let diagnosticManager: DiagnosticManager;

  beforeEach(() => {
    diagnosticManager = new DiagnosticManager();
  });

  test('should create diagnostic collection', () => {
    expect(diagnosticManager).toBeDefined();
  });

});

