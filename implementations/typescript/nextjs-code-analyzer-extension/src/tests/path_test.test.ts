

import * as path from 'path'
import * as os from 'os';

describe('Path Test', () => {
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


    test('should be defined', () => {
        expect(addon).toBeDefined();
    });

    test('comment', () => {
        expect(addon.CreateReport).toBeDefined();
    });
});
  
