#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Matrix {
private:
  int num_rows_;
  int num_columns_;

  vector<vector<char>> elements_;

public:
  Matrix() {
    num_rows_ = 0;
    num_columns_ = 0;
  }

  Matrix(int num_rows, int num_columns) {
    Reset(num_rows, num_columns);
  }

  void Reset(int num_rows, int num_columns) {
    if (num_rows < 0) {
      throw out_of_range("num_rows must be >= 0");
    }
    if (num_columns < 0) {
      throw out_of_range("num_columns must be >= 0");
    }
    if (num_rows == 0 || num_columns == 0) {
      num_rows = num_columns = 0;
    }

    num_rows_ = num_rows;
    num_columns_ = num_columns;
    elements_.assign(num_rows, vector<char>(num_columns));
  }

  char& At(int row, int column) {
    return elements_.at(row).at(column);
  }

  char At(int row, int column) const {
    return elements_.at(row).at(column);
  }

  int GetNumRows() const {
    return num_rows_;
  }

  int GetNumColumns() const {
    return num_columns_;
  }
};

bool operator==(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    return false;
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    return false;
  }

  for (int row = 0; row < one.GetNumRows(); ++row) {
    for (int column = 0; column < one.GetNumColumns(); ++column) {
      if (one.At(row, column) != two.At(row, column)) {
        return false;
      }
    }
  }

  return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix result(one.GetNumRows(), one.GetNumColumns());
  for (int row = 0; row < result.GetNumRows(); ++row) {
    for (int column = 0; column < result.GetNumColumns(); ++column) {
      result.At(row, column) = one.At(row, column) + two.At(row, column);
    }
  }

  return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row) {
    for (int column = 0; column < num_columns; ++column) {
      in >> matrix.At(row, column);
    }
  }

  return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
  for (int row = 0; row < matrix.GetNumRows(); ++row) {
    for (int column = 0; column < matrix.GetNumColumns(); ++column) {
      if (column > 0) {
        out << " ";
      }
      out << matrix.At(row, column);
    }
    out << endl;
  }

  return out;
}

map<char, int> BuildCharZero(const Matrix& m) {
    map<char, int> counters;
    for (int j = 0; j < m.GetNumRows(); j++) {
        ++counters[m.At(j, 0)];
    }
    return counters;
}

map<char, int> BuildCharOne(const Matrix& m) {
    map<char, int> counters;
    for (int j = 0; j < m.GetNumRows(); j++) {
        ++counters[m.At(j, 1)];
    }
    return counters;
}

map<char, int> BuildCharTwo(const Matrix& m) {
    map<char, int> counters;
    for (int j = 0; j < m.GetNumRows(); j++) {
        ++counters[m.At(j, 2)];
    }
    return counters;
}

map<char, int> BuildCharThree(const Matrix& m) {
    map<char, int> counters;
    for (int j = 0; j < m.GetNumRows(); j++) {
        ++counters[m.At(j, 3)];
    }
    return counters;
}

template <typename It>
int PrintMapRange(It range_begin, It range_end) {
    int counter = 0;
    cout << endl;
    for(auto it = range_begin; it != range_end; ++it) {
        counter++;
        cout << it->first << '/' << it->second << " ";
    }
    cout << endl;
    return counter;
}

void PrintMap(const map<char, int>& m) {
    cout << "Size = " << m.size() << endl; //размер алфавита
    auto x = max_element(m.begin(), m.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) { return p1.second < p2.second; });
    cout << "Max element: " << x->first << " " << x->second << endl;
    auto it = m.find(x->first); //максимальное число
    cout << PrintMapRange(it, end(m)) << endl; //наш сдвиг

    int res = m.size() - PrintMapRange(it, end(m));

    for (auto item : m) {
        cout << item.first << ": " << item.second << ", ";
    }
    auto It = std::next(m.begin(), res);
    cout << endl << endl << endl << It->first << endl << endl << endl;

    for (auto item: m) {
        cout << item.first << ": " << item.second << ", ";
    }
    cout << endl;
}

int main() {
   vector<char> s;
    int c;
    cin >> c;
    string a;
    cin >> a;
    for(auto i : a) {
        s.push_back(i);
    }
    cout << a.size() << " " << a.size() / c << endl;
    Matrix m;
    cin >> m;
    cout << m;

    PrintMap(BuildCharZero(m));
    PrintMap(BuildCharOne(m));
    PrintMap(BuildCharTwo(m));
    PrintMap(BuildCharThree(m));

    return 0;
}


//ТЗВПФФЩЧЙЗ_ШПЦБКГЧАШУЫБФДХЩИГЩВШМЪРЩТОСХЧСРЫОИШКЦГРЩТМАШЕХЦПГТСФГЖРЭКНРЩТЖБЧВУРШСЗЯЩФНХППЖЦЬГЩЫШФЦБЬ_ЗБЙОЦВШФЦЪЙПРЮТВЗ_ЪТЧГЫОИЦЬГРЮЮТШЭКЪРОЙРНЧОЧЗБШЙМЩЧЙХЮДРРРПБЗГЫЦШЯУХЪУКРРРЩТУЯЫДЗ_ЪТЧГЫОИЮТВЗШКЖРБТЦЗУЙЫИБЬСЦБЬМЗЯЬГЪЦЯСЦЬШЗРЩЙУШЩПРИРТГЧЦЪЙМСАМЗХКСХЛЯГЪЦХЙЬЯЧСВЦЙХНВТГХСЩФРЭПФЗАКХЩЗТЦИЮДГХСЙИКГЫЦЦАШСХОЗГЩУИЛГРЫГХЩСОЦЪЙУЦЬШХЦЪЙУШЯЩЧЩЫКСРПЙЦНЬПШЦЮДГДВШГИЮКПЦФШЖВЦЙЧЩВЪТСБЬЖИРШЕАСЗЭРЦЫВЗБЙДЧ_КФИВЭФЦЪЙЦНЬПШЦЮЧТСРФТФ_КСРЩЙУЦБЪЙМБЬЖЦЭЙАУЦФЦШЩАЙЩЫТЩЗЩЦУЫЬЕХЦУЙЖЗЫШЦЦАДЙЗ_ЪЙЦТЪДПГЗЦЩПЙЛКГФТКЛПГТЯХЙЙСЧМЖРЩТЩЬПГЦЖТШШЯМОРРКСИЬШЗЦУШЗЦРЫМЛЮКПИРЦЙОХЭЗЦАШИХСИГЪЦХЙЬЯЧСИПЙХЪСЧЪРПЙЖВХКЙЪР_МЬАШЖЦЪЙХРФЧДУРФТИЫЫМИЬЕСВЦЙОИТППРРШЕВЗЧТЗЩЫУЦЬЕЛЫЦЦЯНРФДЙЦХ_ХЛЦГЪЦХЙКЩОЙХЩПРЗ_ШЦНЮ_МИЬЕСЦРШЕУСОДЕВЙЕЦЬПЙЗИТФЦЫШНЗ_ШПЦБШНЗ_ЪТЧГЫОИЮТВЗЗПРЗБЬДХХКФЪЮДЙЗВППНДШСХЛПГЧАШЖЦХКГЧЯЫОЦЬЕОЫРЩФНХЧДПЮКЫНЮДГМЬИГЧЦЪЙМСАМЗУДХЦЫШЫИБЬТЪЮДЩЗУТИНЯЫМЛЮКПЦУЙТМЮКОЦРЫЙЛЯОСЖРЫМЩВПРВРФДЙЦХ_ХЯНТЗВМГХЦЙУНАПИИОЬГЙЩЬЯЗБМТРРЬФРРЬЯЩПАМЗБПРГХПХЖВЙУЖВЕГКЩОЙЦЫКСИЬШЖЗЯЧМЗВЪДХБХМШГЗЦЗ_ШГИЮКПЦФШЖЦЪЙЦНЕЧТУЯНМРРФТИЫЫМИЬЕСВЦЙОИТППРРМУЦЬЧЙЗБЩТЩЯЛСВРЩФЦ_ЭХТСЬ_ЗБШЦХЩЙРРЬХМЦЮШЖЗЩЙИИЧПГФЩХПРСЪИЗТТЦЗУЙХНЫЭСМГЙСЦРОПЖРЩЙШЦОДЯЩЙЪРДЪТКЯУГРЮЮТШЭКЪРЩЙМЭРЩФРХПЦЩПЙИЦ_ШПХЩЬ_ЗЮШЖВЭТГТЯЦРЫВТФЫОВМФЩЙЧЩВЪТСБЬЖИЭТГКЯХТТЯЧСЦРШУЪЩАЙЩЫТНЗЫКЕНЬЕГМСХ_ХЦУГЩУИЛРРЧЙЩГВМСРЫЙФЮКИЮСЬ_ЗЭТПУЩКФМСЙЕРВЙЖЗБПОЫЮОЧЗЯЬГЦХЧТЛЯЙУЦУЬТШЩЬЙУПЙЫЪЯЙЦЦРМФЦХПГЫБТПРВППЖРОТЗХЪЧЛЯНТЗЯЛЙЩ_ПЫРУКЙЪРЩТУЯЫЧЗ_ЪТЧГЫОИЮТВЗХШХЪСЬТЯЮЭБЗХХВЗУПИНЮТВЗХМДМЖКЦРРЩВЪЩЙЦВБИЫЗВППНДШСХЛЯГШССЗЦУШФЦУЙТМЮШЖШЦЦЙХЮШГЯЩЫПЦРЬДТЩЯГШССЗЦУШФЦУЙРЦЧЧТЗБЭЭНБЬЖНЮЧТЗГМЙУЩАМЪМЙЛИРЫЫНВЙХОСЬМЖРЭИИЬИВЗЩСЕВВШЫХГЗГРЮЮТШЭКЪРОЙЩЦВИГЙЛЙУИГСЯЗЭПКМГЙХУЯМДФЩЙМЗДЪДПСЦМЗЭЧТЛЩПГЧАПИЧАТВЪЩИГМЬИГЧЯООУОАЙХЩИГТРТСЪЦЪСНВЙУЦЬЕЛЫОЬХЖРШХЦТДРЗВТУЦЭЙЦНЬПШЦЮЧТСРХМХЩТГЦЮКГЦТХДМСПЦЗБЪДКЮТЦНЬЕСЦРМЯЩЯФТСРЩФЦ_ЭХТЮШНЗБЩТЩЯЛСЦБЬ_ЕРЩТМ_ТХЯЩФМЗЦРЙФЦЫВЯЮШГЧЬКЦЖВЙРНБЬСЦЪЙЦНЬПШЦЮЧТСРФТФ_КСРЩЙЛИРЖОЩ_ХЧИВКЪРОЙПРЮТМЗ_ШГТЯЬТШЯУГРЕЙИИЮЧЯНРЩЙШЦОДЕВЫВЗЮКГЙЬТКИЪБЧЕРЬТЯЫЭГКЕШИИРМГРЮЬЙШЮПЦЗСЙЦИЫРЙЗЯЩПИЗТЖИОЬГЫБХЧЛЩЙОЦЭЩДХЩТГЦТПХЧЦАМКСЗЭНЪЙУЦХФПЕЗПСРЦЙОЗЩЧЦНАЧЙЪРЩТЗЦОМХЯУГЩВКЖТЦЙУЦАИИТСЙИКСОЪИВЕГЪЛЫВЯРОТУЬКФЦУЙЖЗФШИЗНЬМЗЦРЙЛЯОСВЦЙЖПЮШХВРЪДПЭПФЗЫШЦЦАДЩЗУДЫРБХВНВЫВЗБЙЧЯЦЬТФРЩФЦ_ЭХТЮШНЗБЩТЩЯЛСЦБЬМЗЬТСРЩЙУЦЬЧТЩВЕБЗ_ШОШЛМДЕВЙЖЩЦЙФИБЯТМЛЙСИРТСЪЦЪСНВЙМЗ_ЪМЗНЬТФРЧЙЗУККХЯЙУЦБЬТЖЮЧТЗАКЕЦВКБЪРЩТМ_ТХЯЩФМЗБЙАЪЯУГЩЦЬ_ЕРТПРРМТЦТВЙЗЦУГХЦЙУЦЬЕЛЫОЬХЖРЩЙШЦОДЕВЙИИЮЧЯНРЧДЗЮПХТЯХ_ТЯЙОРЬШРНВЪТКРТПРРЧДЗХЪЧЛЯУГТАКНЗБМЙЪСЙМПРЫЧФЭДГДВТЩЗ_ХДЪЦРЙСРТГЬЩЧДХБТФЫЦЬХЖРМХЖРЫЙЪМЙМХВПФХЦЬ
//влцдутжбюцхъяррмшбрхцэооэцгбрьцмйфктъъюьмшэсяцпунуящэйтаьэдкцибрьцгбрпачкъуцпъбьсэгкцъгуущарцёэвърюуоюэкааэбрняфукабъарпяъафкъиьжяффнйояфывбнэнфуюгбрьсшьжэтбэёчюъюръегофкбьчябашвёэуъъюаднчжчужцёэвлрнчулбюпцуруньъшсэюъзкцхъяррнрювяспэмасчкпэужьжыатуфуярюравртубурьпэщлафоуфбюацмнубсюкйтаьэдйюнооэгюожбгкбрънцэпотчмёодзцвбцшщвщепчдчдръюьскасэгъппэгюкдойрсрэвоопчщшоказръббнэугнялёкьсрбёуыэбдэулбюасшоуэтъшкрсдугэфлбубуъчнчтртпэгюкиугюэмэгюккъъпэгяапуфуэзьрадзьжчюрмфцхраююанчёчюъыхьъцомэфъцпоирькнщпэтэузуябащущбаыэйчдфрпэцъьрьцъцпоилуфэдцойэдятррачкубуфнйтаьэдкцкрннцюабугюуубурьпйюэъжтгюркующоъуфъэгясуоичщщчдцсфырэдщэъуяфшёчцюйрщвяхвмкршрпгюопэуцчйтаьэдкцибрьцыяжтюрбуэтэбдуящэубъибрювъежагибрбагбрымпуноцшяжцечкфодщоъчжшйуъцхчщвуэбдлдъэгясуахзцэбдэулькнъщбжяцэьрёдъьвювлрнуяфуоухфекьгцчччгэъжтанопчынажпачкъуъмэнкйрэфщэъьбудэндадъярьеюэлэтчоубъцэфэвлнёэгфдсэвэёкбсчоукгаутэыпуббцчкпэгючсаъбэнэфъркацхёваетуфяепьрювържадфёжбьфутощоявьъгупчршуитеачйчирамчюфчоуяюонкяжыкгсцбрясшчйотъъжрсщчл