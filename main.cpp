#include <iostream>
#include <fstream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ListSequence.h"
#include "ArraySequence.h"

bool odd(int a){
    return a%2==0;
}

int main() {
    char cmd, cmd2;
    int tpe, pntr=0, size, id, id2, aid, aid2, el, cse;
    int* data = nullptr;
    std::ofstream out("Result.txt");
    if(!out.is_open()){
        std::cerr << "Output file wasn't opened. Tests cannot be run.";
        return -1;
    }
    std::cin >> tpe;
    switch(tpe) {
        case 1: {
            std::ifstream in("DynamicTest.txt");
            if (!in.is_open()) {
                std::cerr << "DynamicTest file wasn't opened. Tests cannot be run.";
                return -1;
            }
            auto *arrays = new DynamicArray<int>[10];
            while (in >> cmd) {
                switch (cmd) {
                    case 'n': {
                        if (pntr == 10) {
                            out << "TestError: there are cannot be more that 10 arrays in that test.";
                            return -1;
                        }
                        in >> cmd2;
                        switch (cmd2) {
                            case 'n': {
                                in >> size;
                                delete[] data;
                                data = new int[size];
                                for (int i = 0; i < size; i++) {
                                    in >> data[i];
                                }
                                arrays[pntr] = DynamicArray<int>(data, size);
                                break;
                            }
                            case 's': {
                                in >> size;
                                arrays[pntr] = DynamicArray<int>(size);
                                break;
                            }
                            case 'c': {
                                in >> id;
                                arrays[pntr] = DynamicArray<int>(arrays[id]);
                                break;
                            }
                            default:
                                out << "TestError: unidentified second command.";
                                return -1;
                        }
                        pntr++;
                        break;
                    }
                    case 'e': {
                        in >> cmd2;
                        switch (cmd2) {
                            case 'o': {
                                in >> id;
                                out << arrays[id] << std::endl;
                                break;
                            }
                            case 'g': {
                                in >> id;
                                in >> aid;
                                out << arrays[id].get(aid) << std::endl;
                                break;
                            }
                            case 'l': {
                                in >> id;
                                out << arrays[id].getSize() << std::endl;
                                break;
                            }
                            case 's': {
                                in >> id >> aid >> el;
                                arrays[id].set(aid, el);
                                break;
                            }
                            case 'r': {
                                in >> id >> size;
                                arrays[id].resize(size);
                                break;
                            }
                            default:
                                out << "TestError: unidentified second command.";
                                return -1;
                        }
                        break;
                    }
                    default:
                        out << "TestError: unidentified first command.";
                        return -1;
                }
            }
            delete[] arrays;
            in.close();
            break;
            }
        case 2: {
            std::ifstream in("LinkedTest.txt");
            if (!in.is_open()) {
                std::cerr << "LinkedTest file wasn't opened. Tests cannot be run.";
                return -1;
            }
            LinkedList<int> *lists[10];
            while (in >> cmd) {
                switch (cmd) {
                    case 'n': {
                        if (pntr == 10) {
                            out << "TestError: there are cannot be more that 10 lists in that test.";
                            return -1;
                        }
                        in >> cmd2;
                        switch (cmd2) {
                            case 'a': {
                                in >> size;
                                delete[] data;
                                data = new int[size];
                                for (int i = 0; i < size; i++) {
                                    in >> data[i];
                                }
                                lists[pntr] = new LinkedList<int>(data, size);
                                break;
                            }
                            case 'e': {
                                lists[pntr] = new LinkedList<int>();
                                break;
                            }
                            case 'c': {
                                in >> id;
                                lists[pntr] = new LinkedList<int>(*lists[id]);
                                break;
                            }
                            case 's': {
                                in >> id >> aid >> aid2;
                                lists[pntr] = lists[id]->getSublist(aid, aid2);
                                break;
                            }
                            case 'k': {
                                in >> id >> id2;
                                lists[pntr] = lists[id]->concat(lists[id2]);
                                break;
                            }
                            default:
                                out << "TestError: unidentified second command.";
                                return -1;
                        }
                        pntr++;
                        break;
                    }
                    case 'e': {
                        in >> cmd2;
                        switch (cmd2) {
                            case 'o': {
                                in >> id;
                                out << *(lists[id]) << std::endl;
                                break;
                            }
                            case 'f': {
                                in >> id;
                                out << lists[id]->getFirst() << std::endl;
                                break;
                            }
                            case 'l': {
                                in >> id;
                                out << lists[id]->getLast() << std::endl;
                                break;
                            }
                            case 'g': {
                                in >> id >> aid;
                                out << lists[id]->get(aid) << std::endl;
                                break;
                            }
                            case 's': {
                                in >> id;
                                out << lists[id]->getLength() << std::endl;
                                break;
                            }
                            case 'a': {
                                in >> id >> el;
                                lists[id]->append(el);
                                break;
                            }
                            case 'p': {
                                in >> id >> el;
                                lists[id]->prepend(el);
                                break;
                            }
                            case 'i': {
                                in >> id >> aid >> el;
                                lists[id]->insertAt(el, aid);
                                break;
                            }
                            default:
                                out << "TestError: unidentified second command.";
                                return -1;
                        }
                        break;
                    }
                    default:
                        out << "TestError: unidentified first command.";
                        return -1;
                }
            }
            for (int i = 0; i < pntr; ++i) {
                delete lists[i];
            }
            in.close();
            break;
            }
        case 3: {
            std::ifstream in("SequenceTest.txt");
            if (!in.is_open()) {
                std::cerr << "SequenceTest file wasn't opened. Tests cannot be run.";
                return -1;
            }
            Sequence<int> *conts[25];
            while (in >> cmd) {
                switch (cmd) {
                    case 'n': {
                        if (pntr == 25) {
                            out << "TestError: there are cannot be more that 25 sequences in that kind of test.";
                            return -1;
                        }
                        in >> cmd2;
                        switch (cmd2) {
                            case 'n': {
                                in >> cse >> size;
                                delete[] data;
                                data = new int[size];
                                for (int i = 0; i < size; i++) {
                                    in >> data[i];
                                }
                                switch (cse) {
                                    case 0:
                                        conts[pntr] = new MutableArraySequence<int>(data, size);
                                        break;
                                    case 1:
                                        conts[pntr] = new ImmutableArraySequence<int>(data, size);
                                        break;
                                    case 2:
                                        conts[pntr] = new MutableListSequence<int>(data, size);
                                        break;
                                    case 3:
                                        conts[pntr] = new ImmutableListSequence<int>(data, size);
                                        break;
                                    default:
                                        out << "TestError: unidentified third command.";
                                        return -1;
                                }
                                break;
                            }
                            case 'e': {
                                in >> cse;
                                switch (cse) {
                                    case 0:
                                        conts[pntr] = new MutableArraySequence<int>();
                                        break;
                                    case 1:
                                        conts[pntr] = new ImmutableArraySequence<int>();
                                        break;
                                    case 2:
                                        conts[pntr] = new MutableListSequence<int>();
                                        break;
                                    case 3:
                                        conts[pntr] = new ImmutableListSequence<int>();
                                        break;
                                    default:
                                        out << "TestError: unidentified third command.";
                                        return -1;
                                }
                                break;
                            }
                            case 'c': {
                                in >> cse >> id;
                                switch (cse) {
                                    case 0:
                                        conts[pntr] = new MutableArraySequence<int>(*(conts[id]));
                                        break;
                                    case 1:
                                        conts[pntr] = new ImmutableArraySequence<int>(*(conts[id]));
                                        break;
                                    case 2:
                                        conts[pntr] = new MutableListSequence<int>(*(conts[id]));
                                        break;
                                    case 3:
                                        conts[pntr] = new ImmutableListSequence<int>(*(conts[id]));
                                        break;
                                    default:
                                        out << "TestError: unidentified third command.";
                                        return -1;
                                }
                                break;
                            }
                            case 's': {
                                in >> id >> aid >> aid2;
                                conts[pntr] = conts[id]->getSubsequence(aid, aid2);
                                break;
                            }
                            case 'a': {
                                in >> id >> el;
                                conts[pntr] = conts[id]->append(el);
                                break;
                            }
                            case 'p': {
                                in >> id >> el;
                                conts[pntr] = conts[id]->prepend(el);
                                break;
                            }
                            case 'i': {
                                in >> id >> el >> aid;
                                conts[pntr] = conts[id]->insertAt(el, aid);
                                break;
                            }
                            case 'k': {
                                in >> id >> id2;
                                conts[pntr] = conts[id]->concat(conts[id2]);
                                break;
                            }
                            default:
                                out << "TestError: unidentified second command.";
                                return -1;
                        }
                        pntr++;
                        break;
                    }
                    case 'e': {
                        in >> cmd2;
                        switch (cmd2) {
                            case 'o': {
                                in >> id;
                                out << *(conts[id]) << std::endl;
                                break;
                            }
                            case 'f': {
                                in >> id;
                                out << conts[id]->getFirst() << std::endl;
                                break;
                            }
                            case 'l': {
                                in >> id;
                                out << conts[id]->getLast() << std::endl;
                                break;
                            }
                            case 'g': {
                                in >> id >> aid;
                                out << conts[id]->get(aid) << std::endl;
                                break;
                            }
                            case 's': {
                                in >> id;
                                out << conts[id]->getLength() << std::endl;
                                break;
                            }
                            default:
                                out << "TestError: unidentified second command.";
                                return -1;
                        }
                        break;
                    }
                    default:
                        out << "TestError: unidentified first command.";
                        return -1;
                }
            }
            break;
        }
        default:
            std::cerr << "Illogical input.";
            return -1;
    }
    delete[] data;
    int a[5] = {1, 2, 3, 4, 5}, count;
    auto* b = new MutableArraySequence<int>(a, 5);
    auto** c = b->split(odd, count);
    for (int i = 0; i < count; i++) {
        out << *c[i] << " ";
    }
    for (int i = 0; i < count; i++) {
        delete c[i];
    }
    delete[] c;
    delete b;
    out.close();
    return 0;
}
