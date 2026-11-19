#include <unity.h>
#include <string>
#include "AusfahrtLogik.h"



// Spy: zeichnet Schranken-Aufrufe auf
class SpySchranke : public ISchranke {
public:
    int öffnenAufrufe = 0;
    int schliessenAufrufe = 0;
    void öffnen() override { öffnenAufrufe++; }
    void schliessen() override { schliessenAufrufe++; }
};

// Stub: steürbare Zeit
class StubZeit : public IZeitqülle {
public:
    unsigned long jetzt = 0;
    unsigned long jetztMillis() override { return jetzt; }
};

// Fake: vereinfachte Speicher-Implementierung (Map -> hier reicht eine kleine Struktur)
class FakeSpeicher : public ISpeicher {
public:
    struct Eintrag { unsigned long einfahrt; bool bezahlt; };
    std::map<std::string, Eintrag> fahrzeuge;

    void einfahren(const std::string& k, unsigned long t) override { fahrzeuge[k] = {t, false}; }
    bool istBezahlt(const std::string& k) override {
        auto it = fahrzeuge.find(k);
        return it != fahrzeuge.end() && it->second.bezahlt;
    }
    void setzeBezahlt(const std::string& k) override {
        auto it = fahrzeuge.find(k);
        if (it != fahrzeuge.end()) it->second.bezahlt = true;
    }
    void ausfahren(const std::string& k) override { fahrzeuge.erase(k); }
    bool istAnwesend(const std::string& k) override { return fahrzeuge.count(k) > 0; }
};

void test_einfahrt_speichert_fahrzeug() {
    SpySchranke schranke; StubZeit zeit; FakeSpeicher speicher;
    AusfahrtLogik logik(schranke, zeit, speicher, 3000);

    logik.fahrzeugEingefahren("ZH 12345");

    TEST_ASSERT_TRUE(speicher.istAnwesend("ZH 12345"));
    TEST_ASSERT_FALSE(speicher.istBezahlt("ZH 12345"));
}

void test_bezahlung_setzt_status() {
    SpySchranke schranke; StubZeit zeit; FakeSpeicher speicher;
    AusfahrtLogik logik(schranke, zeit, speicher, 3000);

    logik.fahrzeugEingefahren("ZH 12345");
    bool ok = logik.bezahle("ZH 12345");

    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_TRUE(speicher.istBezahlt("ZH 12345"));
}

void test_ausfahrt_ohne_bezahlung_verweigert() {
    SpySchranke schranke; StubZeit zeit; FakeSpeicher speicher;
    AusfahrtLogik logik(schranke, zeit, speicher, 3000);

    logik.fahrzeugEingefahren("ZH 12345");
    bool geöffnet = logik.ausfahrtAnfordern("ZH 12345");

    TEST_ASSERT_FALSE(geöffnet);
    TEST_ASSERT_EQUAL_INT(0, schranke.öffnenAufrufe);
}

void test_ausfahrt_mit_bezahlung_öffnet_schranke() {
    SpySchranke schranke; StubZeit zeit; FakeSpeicher speicher;
    AusfahrtLogik logik(schranke, zeit, speicher, 3000);

    logik.fahrzeugEingefahren("ZH 12345");
    logik.bezahle("ZH 12345");
    bool geöffnet = logik.ausfahrtAnfordern("ZH 12345");

    TEST_ASSERT_TRUE(geöffnet);
    TEST_ASSERT_EQUAL_INT(1, schranke.öffnenAufrufe);
}

void test_kennzeichen_nach_ausfahrt_entfernt() {
    SpySchranke schranke; StubZeit zeit; FakeSpeicher speicher;
    AusfahrtLogik logik(schranke, zeit, speicher, 3000);

    logik.fahrzeugEingefahren("ZH 12345");
    logik.bezahle("ZH 12345");
    logik.ausfahrtAnfordern("ZH 12345");

    TEST_ASSERT_FALSE(speicher.istAnwesend("ZH 12345"));
}

void test_schranke_schliesst_nach_ablauf() {
    SpySchranke schranke; StubZeit zeit; FakeSpeicher speicher;
    AusfahrtLogik logik(schranke, zeit, speicher, 3000);

    logik.fahrzeugEingefahren("ZH 12345");
    logik.bezahle("ZH 12345");
    logik.ausfahrtAnfordern("ZH 12345");   // öffnet bei t=0

    zeit.jetzt = 2999;
    logik.aktualisiere();
    TEST_ASSERT_EQUAL_INT(0, schranke.schliessenAufrufe);

    zeit.jetzt = 3000;
    logik.aktualisiere();
    TEST_ASSERT_EQUAL_INT(1, schranke.schliessenAufrufe);
}

int main(int, char**) {
    UNITY_BEGIN();
    RUN_TEST(test_einfahrt_speichert_fahrzeug);
    RUN_TEST(test_bezahlung_setzt_status);
    RUN_TEST(test_ausfahrt_ohne_bezahlung_verweigert);
    RUN_TEST(test_ausfahrt_mit_bezahlung_öffnet_schranke);
    RUN_TEST(test_kennzeichen_nach_ausfahrt_entfernt);
    RUN_TEST(test_schranke_schliesst_nach_ablauf);
    return UNITY_END();
}
