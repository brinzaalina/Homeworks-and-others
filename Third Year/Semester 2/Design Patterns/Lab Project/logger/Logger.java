package logger;

import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Logger {
    // Singleton design pattern
    private static Logger instance = null;
    private static final String LOG_FILE = "log.txt";
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    private Logger() {
    }

    public static Logger getInstance() {
        if (instance == null) {
            instance = new Logger();
        }

        return instance;
    }

    public void log(String message) {
        LocalDateTime now = LocalDateTime.now();
        String logMessage = "[" + now.format(DATE_FORMATTER) + "] " + message;
        try (FileWriter writer = new FileWriter(LOG_FILE, true)) {
            writer.write(logMessage + "\n");
            writer.flush();
        } catch (IOException e) {
            System.out.println("Failed to log message: " + logMessage);
            e.printStackTrace();
        }
    }
}
