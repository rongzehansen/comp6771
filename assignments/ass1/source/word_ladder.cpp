#include <comp6771/word_ladder.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>

auto is_one_char_away(std::string const& src, std::string const& trg) -> bool {
	auto i_src = src.cbegin();
	auto i_trg = trg.cbegin();
	// previous character not equal set to false
	auto prev_char_ne = false;
	for (; i_src < src.cend(); i_src++, i_trg++) {
		if (*i_src != *i_trg) {
			if (prev_char_ne == false) {
				// allow a character to be different for the first time
				prev_char_ne = true;
			}
			else {
				// return false if trg has another different character
				return false;
			}
		}
	}
	return prev_char_ne;
}

auto get_words_by_len(std::unordered_set<std::string> const& lexicon, int const& len)
   -> std::unordered_set<std::string> {
	std::unordered_set<std::string> words;
	std::copy_if(lexicon.begin(),
	             lexicon.end(),
	             std::inserter(words, words.begin()),
	             [len](auto const x) { return x.size() == len; });
	return words;
}

auto gen_grf_from_words(std::string const& from, std::unordered_set<std::string> words)
   -> std::unordered_map<std::string, std::vector<std::string>> {
	std::unordered_map<std::string, std::vector<std::string>> graph;
	std::queue<std::string> queue;
	std::unordered_set<std::string> prev_vtxs;
	queue.push(from);
	words.erase(from);
	while (!queue.empty()) {
		for (auto i = queue.size(); i > 0; i--) {
			auto curr_word = queue.front();
			queue.pop();
			for (auto j = words.cbegin(); j != words.cend(); j++) {
				if (is_one_char_away(curr_word, *j)) {
					graph[curr_word].push_back(*j);
					if (!prev_vtxs.contains(*j)) {
						prev_vtxs.insert(*j);
						queue.push(*j);
					}
				}
			}
		}
		for (auto k = prev_vtxs.cbegin(); k != prev_vtxs.cend(); k++) {
			words.erase(*k);
		}
		prev_vtxs.clear();
	}
	return graph;
}

auto get_paths_from_grf(std::string const& from,
                        std::string const& to,
                        std::unordered_map<std::string, std::vector<std::string>> const& graph)
   -> std::vector<std::vector<std::string>> {
	std::vector<std::vector<std::string>> paths;
	std::queue<std::vector<std::string>> queue;
	queue.push({from});
	while (!queue.empty()) {
		auto curr_path = queue.front();
		queue.pop();
		auto curr_word = curr_path.back();
		if (curr_word == to) {
			paths.push_back(curr_path);
		}
		if (graph.find(curr_word) != graph.end()) {
			for (auto i : graph.find(curr_word)->second) {
				auto new_path = std::vector<std::string>(curr_path);
				new_path.push_back(i);
				queue.push(new_path);
			}
		}
	}
	return paths;
}

namespace word_ladder {

	[[nodiscard]] auto generate(std::string const& from,
	                            std::string const& to,
	                            std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		auto const len = from.size();
		auto const words = get_words_by_len(lexicon, len);
		auto const graph = gen_grf_from_words(from, words);
		auto  paths = get_paths_from_grf(from, to, graph);
		/*
		for (auto i = words.begin(); i != words.end(); i++) {
		   std::cout << *i << std::endl;
		}
		*/
		std::sort(paths.begin(), paths.end());
		return paths;
	}

} // namespace word_ladder
