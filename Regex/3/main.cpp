#include <iostream>
#include <regex>
#include <string>

/*  Интернет говорит, что:
 *      1) в логине могут быть буквы, цифры, подчеркивания, -, точка.
 *          Регистр значения не имеет.
 *          Длинна от 3-х символов.
 *
 *      2) в домене могут быть буквы, цифры, -, минимальная длина 2 символа.
 *          Не может начинаться и заканчиваться на "-".
 *          Может быть домен из 3-х частей.
 * */

using namespace std;

class Email_research {
private:
    std::regex pattern;

public:
    Email_research() {
        regex _pattern(R"(\b(([\w][\w_\.-]+[\w])(@)([\w][\w_-]*[\w]\.){1,2}([\w][\w_-]*[\w]))\b)");
        pattern = _pattern;
    }

    auto get_email_from_text(const string& str) {
        std::sregex_iterator begin(str.cbegin(), str.cend(), pattern);
        std::sregex_iterator end;

        vector<string> result;
        std::for_each(begin, end, [](const std::smatch & m) {
            auto name_domain = m[4].str() + m[5].str() + m[6].str();
            std::cout << m[0] << " -> " << name_domain << std::endl;
        });
    }
};

int main(int argc, char ** argv)
{
    std::string data = " Adm.in@ocomp.info \n"
                       " Dima@ma-il.ru \n"
                       " Alex@yaf.ru \n"
                       "hfg gjv-v_h__s_m-sh___h---hh@mghuf.ry dhfg\n"
                       "dg2fs45@dsfg.dsg\n"
                       "last@gmail.com\n"
                       "first76_4last@gmail.com\n"
                       "123sdf@MAXIMALNAYA-DLINA-DOMENNOGO-IMENI-NE-DOLZHNA-PREVYSHAT-63-BUKAF.RU\n"
                       "1jgv@718281828459045235360287471352662497757247093699959574966967627.RU\n"
                       "\n"
                       "dg2fs45@dsfg.dsg.dfg .fdg.fdg.dfg.sdg.sdfg.sdg.sg\n"
                       "1_Dsf_df@TAK-KHARLA-MOV-VALENTIN-IZ-VORONEZHA-STAL-ZNAMENIT-VESEGO-ZA-600.RU.ru .ru.ru.\n"
                       "_fhn1@YA-NA-SAMOM-PONTOVOM-SAYTE-V-RUS-S-K-O-MNETE-MOY-NOMER-POSLE-SLESHA.RU-etry-ey\n"
                       "<.tey\n"
                       "dgh> sdfgo@juf.eho sdgs\n"
                       "fgh dgh. gds@khh.ru   dfs@sdfg.f\n"
                       "d hg+ alsdgo@yandex.ru @dfg.sdg\n"
                       "all_o12_zo@jvu.-e-o-\n"
                       "all_o12_zo-@jvu-eo.\n"
                       "all_o12_zo@jvu.j.jge.hgfo\n"
                       "all_o12_zo@jvu.-eo\n"
                       "f.i.r.s.t.l.a.s.t@gmail.com\n"
                       "1@GLEDENOV-POD-KAKIM-TI-NIKOM-SIDISH-NA-FORUME-DOMENFORUM-DOT-NET.RU\n"
                       "1@I-AM-DMITRY-MUKHACH-FROM-SPB-ICQ-3235555-SEARCH-WORK-IN-IT-TECH.RU\n"
                       "1@SAMOEDLINNOEDOMENNOEIMYAVRUSSKOMINTERNETEPRINADLEZHITERIELMEDIA.RU\n"
                       "1@SO-PLEASE-DO-NOT-ASK-ME-WHY-SOME-T-TO-BE-BRAINDAMAGED.RU\n"
                       "1@YAPRISHELKTEBESPRIVETOMRASSKAZATCHTOSOLNCEVSTALODAJDENEGNAPIVKO.RU\n"
                       "1@14159265358-97932384626433-83279502884197169399375105820974944592.RU";

    Email_research r;
    r.get_email_from_text(data);

    return 0;
}