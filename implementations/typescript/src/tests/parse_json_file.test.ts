
import { CodeAnalyzer } from "../code_analyser";
import * as path from "path";

const basePath = process.cwd();
const addonPath = path.join(basePath, '../../../cpp/build/Release/NextJS_Analyser.node');
const filePath = path.join(basePath, './implementations/typescript/src/tests/test_data.js');

test('check if parsed data is correctly commented', () => { // Correct syntax for arrow function
    const analyzer = new CodeAnalyzer(addonPath); // Correct instantiation of the class
    analyzer.analysisFile(filePath);

    let commentValue: [string, string][] = [];
    analyzer.getTokens().map((token: any) => {
        commentValue.push([token.comment.value, token.value]); 
    })

    const expectations = [
        ["Large file detected! Consider refactoring 'use client' into a smaller file \n", "use client"],
        ["Consider refactoring useState Large file detected \n", "useState"], // Removed extraneous characters
        ["Consider refactoring useState Large file detected \n", "useState"],
        ['Consider refactoring useEffect Large file detected \n' +
        'If you are using an async await fetch in your useEffect, consider making this component server side and make this component async. Example: async function Component() {    const var = await fetchFunction();    return (        <div></div>    );}  \n', "useEffect"
        ]
    ];
    
    expect(commentValue.length).toBe(expectations.length);

    commentValue.forEach((tuple, index) => {
        expect(tuple[0]).toBe(expectations[index][0]);
        expect(tuple[1]).toBe(expectations[index][1]); 
    });
});