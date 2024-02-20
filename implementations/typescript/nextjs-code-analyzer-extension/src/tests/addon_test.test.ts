import * as path from 'path'
import * as os from 'os';

describe('Addon Tests', () => {
    let addonPath: any;

    switch(os.platform()) {
        case 'win32':
            addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser_windows.node');
            break;
        case 'darwin':
            // Check architecture
            if (process.arch === 'arm64') {
                // Path for Apple Silicon (M1/M2)
                addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser_macOs_arm64.node');
            } else {
                // Path for Intel-based Mac
                addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser_macOs_x86_64.node');
            }
            break;
        case 'linux':
            addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser_ubuntu.node');
            break;
        default:
            throw new Error('Unsupported platform');
    }

    const addon = require(addonPath);

    let code = `
    {
        "loc": {
            "start": { "line": 0, "index": 0 },
            "end": { "line": 1, "index": 10 }
        },
        "tokens": [  
            {
                "type": {
                    "label": "name",
                    "beforeExpr": false,
                    "startsExpr": true,
                    "rightAssociative": false,
                    "isLoop": false,
                    "isAssign": false,
                    "prefix": false,
                    "postfix": false,
                    "binop": null,
                    "updateContext": null
                },
                "value": "useState",
                "start": 95,
                "end": 103,
                "loc": {
                    "start": {
                        "line": 9,
                        "column": 30,
                        "index": 95
                    },
                    "end": {
                        "line": 9,
                        "column": 38,
                        "index": 103
                    }
                }
            }
        ]
    }
    `

    code = code.toString()
    // Get analysis results from your addon.
    const analysisResults = addon.CreateReport(code);

    console.log('Result', analysisResults.tokens[0].comment.value)

    test('should be defined', () => {
        expect(analysisResults).toBeDefined();
    });

    test('comment', () => {
        expect(analysisResults.tokens[0].comment.value).toBe(
            "No 'use client' detected in 'useState'. If this file contains client-side specific code,consider adding 'use client' for clearer separation of client and server-sidecode, enhancing code organization and performance. \n")
    });

});
  

