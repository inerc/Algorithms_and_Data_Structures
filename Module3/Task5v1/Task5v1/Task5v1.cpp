void compress_string(const string &source, string &compressed){
	std::stringstream str;
	std::map<char, double> frequencies;
	frequencies['e'] = 0.114864;
	frequencies['a'] = 0.078828;
	frequencies['t'] = 0.067567;
	frequencies['i'] = 0.056306;
	frequencies['n'] = 0.065315;
	frequencies['o'] = 0.049549;
	frequencies['s'] = 0.047297;
	frequencies['r'] = 0.054054;
	frequencies['l'] = 0.027027;
	frequencies['d'] = 0.020270;
	frequencies['h'] = 0.024774;
	frequencies['c'] = 0.024774;
	frequencies['u'] = 0.013513;
	frequencies['m'] = 0.013513;
	frequencies['f'] = 0.022522;
	frequencies['p'] = 0.020270;
	frequencies['y'] = 0.011261;
	frequencies['g'] = 0.018018;
	frequencies['w'] = 0.024774;
	frequencies['v'] = 0.006756;
	frequencies['b'] = 0.006756;
	frequencies['k'] = 0.006756;
	frequencies['x'] = 0.002252;
	frequencies['L'] = 0.006756;
	frequencies['q'] = 0.004504;
	frequencies['N'] = 0.002252;
	frequencies['S'] = 0.006756;
	frequencies['E'] = 0.006756;
	frequencies['T'] = 0.002252;
	frequencies['F'] = 0.002252;
	frequencies['U'] = 0.002252;
	frequencies['I'] = 0.002252;
	frequencies['M'] = 0.002252;
	frequencies['1'] = 0.002252;
	frequencies['.'] = 0.006756;
	frequencies['_'] = 0.162162;
	frequencies['2'] = 0.002252;
	frequencies[':'] = 0.004504;
	frequencies['`'] = 0.002252;
	Hufftree<char, double> hufftree(frequencies.begin(), frequencies.end());
	vector<bool> encoded = hufftree.encode(source.begin(), source.end());
	str << encoded << "\n";
	compressed = str.str();
}
void decompress_string(const string &compressed, string &result){
	std::stringstream str;
	std::map<char, double> frequencies;
	frequencies['e'] = 0.114864;
	frequencies['a'] = 0.078828;
	frequencies['t'] = 0.067567;
	frequencies['i'] = 0.056306;
	frequencies['n'] = 0.065315;
	frequencies['o'] = 0.049549;
	frequencies['s'] = 0.047297;
	frequencies['r'] = 0.054054;
	frequencies['l'] = 0.027027;
	frequencies['d'] = 0.020270;
	frequencies['h'] = 0.024774;
	frequencies['c'] = 0.024774;
	frequencies['u'] = 0.013513;
	frequencies['m'] = 0.013513;
	frequencies['f'] = 0.022522;
	frequencies['p'] = 0.020270;
	frequencies['y'] = 0.011261;
	frequencies['g'] = 0.018018;
	frequencies['w'] = 0.024774;
	frequencies['v'] = 0.006756;
	frequencies['b'] = 0.006756;
	frequencies['k'] = 0.006756;
	frequencies['x'] = 0.002252;
	frequencies['L'] = 0.006756;
	frequencies['q'] = 0.004504;
	frequencies['N'] = 0.002252;
	frequencies['S'] = 0.006756;
	frequencies['E'] = 0.006756;
	frequencies['T'] = 0.002252;
	frequencies['F'] = 0.002252;
	frequencies['U'] = 0.002252;
	frequencies['I'] = 0.002252;
	frequencies['M'] = 0.002252;
	frequencies['1'] = 0.002252;
	frequencies['.'] = 0.006756;
	frequencies['_'] = 0.162162;
	frequencies['2'] = 0.002252;
	frequencies[':'] = 0.004504;
	frequencies['`'] = 0.002252;
	Hufftree<char, double> hufftree(frequencies.begin(), frequencies.end());
	vector<bool> encoded;
	for (int i = 0; i < compressed.size(); i++){
		if (compressed.at(i) == '1'){
			encoded.push_back(1);
		}
		else if (compressed.at(i) == '0'){
			encoded.push_back(0);
		}
		else{

		}
	}
	hufftree.decode(encoded, std::back_inserter(result));
}
