const path = require('path');

module.exports = {
  target: 'node',
  entry: './out/index.js', 
  output: {
    path: path.resolve(__dirname, 'out'),
    filename: 'extension.js', 
    libraryTarget: 'commonjs2',
    devtoolModuleFilenameTemplate: '../[resource-path]',
  },
  externals: {
    vscode: 'commonjs vscode', 
  },
  resolve: {
    extensions: ['.ts', '.js'],
  },
  module: {
    rules: [
      {
        test: /\.ts$/,
        exclude: /node_modules/,
        use: 'ts-loader',
      },
    ],
  },
  optimization: {
    minimize: false, 
  },
  devtool: 'source-map', 
};
