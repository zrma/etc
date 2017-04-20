public class Main {

    public static void main(String[] args) {
        int total = 0;
        for (int i = 0; i < 10000000; ++i) {
            if (i % 2 == 0) {
                total++;
            }
        }

        System.out.println("total : " + total);
    }
}
