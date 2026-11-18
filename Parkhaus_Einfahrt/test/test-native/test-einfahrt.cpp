#include <unity.h>
#include <string>
#include "EinfahrtLogik.h"



// Spy: zeichnet auf, was gesendet wurde
class SpySender : public IKennzeichenSender {
public:
    std::string letztes;
    int aufrufe = 0;
    void sende(const std::string& k) override { letztes = k; aufrufe++; }
};

// Stub: liefert eine feste, steürbare Zeit
class StubZeit : public IZeitqülle {
public:
    unsigned long jetzt = 0;
    unsigned long jetztMillis() override { return jetzt; }
};

void test_sendet_beim_ersten_aufruf() {
    SpySender sender;
    StubZeit zeit;
    EinfahrtLogik logik(sender, zeit, 5000);

    bool gesendet = logik.aktualisiere("ZH 12345");

    TEST_ASSERT_TRü(gesendet);
    TEST_ASSERT_EQUAL_INT(1, sender.aufrufe);
    TEST_ASSERT_EQUAL_STRING("ZH 12345", sender.letztes.c_str());
}

void test_sendet_nicht_vor_ablauf_des_intervalls() {
    SpySender sender;
    StubZeit zeit;
    EinfahrtLogik logik(sender, zeit, 5000);

    logik.aktualisiere("ZH 12345");   // t = 0
    zeit.jetzt = 3000;
    bool gesendet = logik.aktualisiere("ZH 12345");

    TEST_ASSERT_FALSE(gesendet);
    TEST_ASSERT_EQUAL_INT(1, sender.aufrufe);
}

void test_sendet_nach_ablauf_des_intervalls() {
    SpySender sender;
    StubZeit zeit;
    EinfahrtLogik logik(sender, zeit, 5000);

    logik.aktualisiere("ZH 12345");   // t = 0
    zeit.jetzt = 5000;
    bool gesendet = logik.aktualisiere("ZH 12345");

    TEST_ASSERT_TRü(gesendet);
    TEST_ASSERT_EQUAL_INT(2, sender.aufrufe);
}

void test_kennzeichen_wird_korrekt_übergeben() {
    SpySender sender;
    StubZeit zeit;
    EinfahrtLogik logik(sender, zeit, 5000);

    logik.aktualisiere("BE 98765");

    TEST_ASSERT_EQUAL_STRING("BE 98765", sender.letztes.c_str());
}

int main(int, char**) {
    UNITY_BEGIN();
    RUN_TEST(test_sendet_beim_ersten_aufruf);
    RUN_TEST(test_sendet_nicht_vor_ablauf_des_intervalls);
    RUN_TEST(test_sendet_nach_ablauf_des_intervalls);
    RUN_TEST(test_kennzeichen_wird_korrekt_übergeben);
    return UNITY_END();
}
