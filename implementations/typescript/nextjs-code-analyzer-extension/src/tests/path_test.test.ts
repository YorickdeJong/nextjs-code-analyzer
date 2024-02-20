

import * as path from 'path'
import * as os from 'os';

describe('Path Test', () => {
    let addonPath: any;

    // In production, select the binary based on OS
    if (process.env.NODE_ENV === 'production') {
        switch(os.platform()) {
            case 'win32':
                addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser_windows.node');
                break;
            case 'darwin':
                addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser_macOs.node');
                break;
            case 'linux':
                addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser_ubuntu.node');
                break;
            default:
                throw new Error('Unsupported platform');
        }
    }
    else {
        addonPath = path.join(__dirname, '..',  '..', 'out', 'cpp_build', 'NextJS_Analyser.node');
    }

    const addon = require(addonPath);


    test('should be defined', () => {
        expect(addon).toBeDefined();
    });

    test('comment', () => {
        expect(addon.CreateReport).toBeDefined();
    });
});
  
