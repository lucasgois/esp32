
import java.net.URL;

class Scratch {
    private static final String LIGAR = "http://192.168.0.19/H1";
    private static final String DESLIGAR = "http://192.168.0.19/L1";

    public static void main(String[] args) throws Exception {

        while (true) {

            comando(DESLIGAR);
            Thread.sleep(500);

            comando(LIGAR);
            Thread.sleep(50);

            comando(DESLIGAR);
            Thread.sleep(50);

            comando(LIGAR);
            Thread.sleep(50);
        }
    }

    private static void comando(String comando) throws Exception {
        URL url = new URL(comando);

        try (var in = url.openStream()) {
            var bytes = in.readAllBytes();
            // System.out.println("bytes = " + new String(bytes));
        }
    }
}