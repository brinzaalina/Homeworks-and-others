module gui {
    requires javafx.base;
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.graphics;

    exports gui;
    opens gui to javafx.fxml;

    exports controller;
    opens controller to javafx.fxml;

    exports exceptions;
    opens exceptions to javafx.fxml;

    exports  model.expression;
    opens model.expression to javafx.fxml;

    exports model.programState;
    opens model.programState to javafx.fxml;

    exports model.statement;
    opens model.statement to javafx.fxml;

    exports model.type;
    opens model.type to javafx.fxml;

    exports model.utils;
    opens model.utils to javafx.fxml;

    exports model.value;
    opens model.value to javafx.fxml;

    exports repository;
    opens repository to javafx.fxml;
}