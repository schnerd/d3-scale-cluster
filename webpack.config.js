var webpack = require('webpack');
var path = require('path');
var libraryName = 'library';
var outputFile = libraryName + '.js';

var config = {
	entry: __dirname + '/src/index.js',
	output: {
		path: __dirname + '/dist',
		filename: 'd3-scale-cluster.min.js',
		library: 'd3scaleCluster',
		libraryTarget: 'umd',
		umdNamedDefine: true
	},
	plugins: [
		new webpack.optimize.UglifyJsPlugin()
	]
};

module.exports = config;
