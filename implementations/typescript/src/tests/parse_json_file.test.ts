
import { CodeAnalyzer } from "../code_analyser";
import * as path from "path";

const basePath = process.cwd();

const filePath = path.join(basePath, 'implementations', 'typescript', 'src', 'test_data', 'test_data_1.js');

test('check if parsed data is correctly commented', () => { // Correct syntax for arrow function
    const analyzer = new CodeAnalyzer(); // Correct instantiation of the class.
    analyzer.analysisFile(filePath);

    let commentValue: [string, string][] = [];
    analyzer.getTokens().map((token: any) => {
        commentValue.push([token.comment.value, token.value]); 
    })  

    console.log('commentValue', commentValue)

    const expectations = [
        ["Large client-side file detected! Consider splitting the current 'use client' fileinto smaller modules. This can improve performance by reducing load times and optimizing resource usage.Review and refactor variables and instances where feasible.\n" +
        ' \n' +
        'Client-side file with a high word count detected. Large amounts of textcan negatively impact SEO and user experience. Consider breaking down the text into smaller,more manageable components, or using server-side rendering for large text elements. \n', "use client"],
        ["Large file detected in 'useState'. Consider breaking downthis file into smaller, more manageable components or usingdynamic imports to optimize performance and code maintainability. \n", "useState"], // Removed extraneous characters
        ["Large file detected in 'useState'. Consider breaking downthis file into smaller, more manageable components or usingdynamic imports to optimize performance and code maintainability. \n", "useState"],
        ["Large file detected in 'useEffect'. Consider breaking downthis file into smaller, more manageable components or usingdynamic imports to optimize performance and code maintainability. \n" +
        "Detected 'useEffect' with async operations. For optimal performance and better handling of asynchronousdata fetching, consider moving this logic to a server-side function or using Next.js's async function <ComponentName>.This can improve data loading efficiency and reduce client-side rendering delays.\n" +
        '\n' +
        'Example of server-side async function:\n' +
        '  async function Component() {\n' +
        '    const data = await fetchFunction();\n' +
        '    return (\n' +
        '        <div>{data}</div>\n' +
        '    );\n' +
        '}\n', "useEffect"
        ]
    ];
    
    expect(commentValue.length).toBe(expectations.length);

    commentValue.forEach((tuple, index) => {
        expect(tuple[0]).toBe(expectations[index][0]);
        expect(tuple[1]).toBe(expectations[index][1]); 
    });
});