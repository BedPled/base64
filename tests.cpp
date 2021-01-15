#include "gtest/gtest.h"
#include "lib.h"
using namespace std;

TEST(askiiToBase, encryption){
    EXPECT_EQ(threeToBase64('A', 'n', 'd'), "QW5k");
    EXPECT_EQ(asciiToBase64("Hello Roman! How are you?"), "SGVsbG8gUm9tYW4hIEhvdyBhcmUgeW91Pw==");
    EXPECT_EQ(asciiToBase64("Hello, I'm Alexander"), "SGVsbG8sIEknbSBBbGV4YW5kZXI=");
    EXPECT_EQ(asciiToBase64("Hello Roman!"), "SGVsbG8gUm9tYW4h");
}

TEST(base64ToAscii, decryption) {
    EXPECT_EQ(fourToAscii('Q', 'W', '5', 'k'), "And");
    EXPECT_EQ(base64ToAscii("SGVsbG8gUm9tYW4hIEhvdyBhcmUgeW91Pw=="), "Hello Roman! How are you?");
    EXPECT_EQ(base64ToAscii("SGVsbG8sIEknbSBBbGV4YW5kZXI="), "Hello, I'm Alexander");
    EXPECT_EQ(base64ToAscii("SGVsbG8gUm9tYW4h"), "Hello Roman!");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
