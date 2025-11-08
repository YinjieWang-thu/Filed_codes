#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <algorithm>
#include <TMVA/Reader.h>
#include <unordered_map>
#include <algorithm>
#include <queue> 
#include "reader.h"

using namespace std;
const Double_t GeV=1000;

void counttri()
{
    const char* infile = "data24_red.root";
    TChain* ch = new TChain("BPHY25");
    ch->Add(infile);
    Init(ch);
    ULong64_t nentries = ch->GetEntries();
    vector<string> words;
    //TFile * f = new TFile(infile);
    //f->cd();


    std::map<std::string, int> ucount;


    for (ULong64_t entry=0; entry<nentries ;entry++) {
        ch->GetEntry(entry);
        if(HLT_name)
        {
            for(string tri:*HLT_name)
            {
                words.push_back(tri);
            }
            if((*HLT_name).size()==1)
            {
                for(string tri:*HLT_name)
                {
                    ucount[tri]++;
                }
            }
        }
    }

    std::unordered_map<std::string, int> freqMap;
    for (const auto& word : words) {
        freqMap[word]++;
    }

    // 2. 定义优先队列（最小堆）保存Top 10
    auto cmp = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second == b.second ? a.first < b.first : a.second > b.second;
    };
    std::priority_queue<
        std::pair<std::string, int>,
        std::vector<std::pair<std::string, int>>,
        decltype(cmp)
    > minHeap(cmp);

    // 3. 遍历词频图，维护Top 10
    for (const auto& entry : freqMap) {
        minHeap.push(entry);
        //if (minHeap.size() > 10) {
        //    minHeap.pop(); // 移除最小元素
        //}
    }

    // 4. 提取结果并反转顺序（从高到低）
    std::vector<std::pair<std::string, int>> topResults;
    while (!minHeap.empty()) {
        topResults.push_back(minHeap.top());
        minHeap.pop();
    }
    std::reverse(topResults.begin(), topResults.end());

    // 5. 输出结果
    std::cout << "freq    unique  Trigger name\n";
    for (const auto& res : topResults) {
        std::cout<<res.second << "\t" << ucount[res.first]<< "\t"<<res.first<<endl;
        //else cout<<"0"<<endl;
    }

}