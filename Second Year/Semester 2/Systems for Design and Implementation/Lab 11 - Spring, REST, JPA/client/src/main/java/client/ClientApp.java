package client;

import client.ui.UI;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class ClientApp {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext("client.config");
        UI console = context.getBean(UI.class);
        console.runConsole();
    }
}
