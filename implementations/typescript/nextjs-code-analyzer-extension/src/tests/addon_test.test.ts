jest.mock('vscode', () => ({
    languages: {
      createDiagnosticCollection: jest.fn(),
    },
}), { virtual: true });


jest.mock('@babel/parser', () => ({
    parse: jest.fn().mockImplementation(() => ({
    type: 'File',
    program: {
      type: 'Program',
      body: [],
      sourceType: 'module'
    }
  })),
  }), { virtual: true });


import * as vscode from 'vscode';
import * as babelParser from '@babel/parser';
import * as path from 'path'

const addonPath = path.join(__dirname, '..', 'cpp_build', 'NextJS_Analyser.node');

describe('Addon Tests', () => {
    const addon = require(addonPath);


    const code = `
        export default function Checkout() {
            const [loading, setLoading] = useState(false);
            const [test, setTest] = useState(false)
        
            const random = useRef();
            const [left, setState] = useState(false); 
            const orderId = uuidv4();
        }
    `
    function passSourceCode(code: string) {
        return babelParser.parse(code, {
            sourceType: "module",
            plugins: [
              "jsx",
              "typescript", 
            ],
            errorRecovery: true,
            ranges: true,
            tokens: true
        });
    }

    const ast = passSourceCode(code)
        
    const astJson = JSON.stringify(ast, null, 2);

    // Get analysis results from your addon
    const analysisResults = addon.CreateReport(astJson);

    console.log(analysisResults.tokens)


});
  
  