package org.example;

import org.example.domain.Student;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import org.example.repository.NotaXMLRepo;
import org.example.repository.StudentXMLRepo;
import org.example.repository.TemaXMLRepo;
import org.example.service.Service;
import org.example.validation.NotaValidator;
import org.example.validation.StudentValidator;
import org.example.validation.TemaValidator;
import org.example.validation.ValidationException;

import static org.junit.jupiter.api.Assertions.*;

//@RunWith(JUnit4.class)
public class TestClass {

    public static Service service;

    @BeforeAll
    public static void setup() {
        StudentValidator studentValidator = new StudentValidator();
        TemaValidator temaValidator = new TemaValidator();
        String filenameStudent = "fisiere/Studenti.xml";
        String filenameTema = "fisiere/Teme.xml";
        String filenameNota = "fisiere/Note.xml";

        StudentXMLRepo studentXMLRepository = new StudentXMLRepo(filenameStudent);
        TemaXMLRepo temaXMLRepository = new TemaXMLRepo(filenameTema);
        NotaValidator notaValidator = new NotaValidator(studentXMLRepository, temaXMLRepository);
        NotaXMLRepo notaXMLRepository = new NotaXMLRepo(filenameNota);
        TestClass.service = new Service(studentXMLRepository, studentValidator, temaXMLRepository, temaValidator, notaXMLRepository, notaValidator);
    }

    @Test
    public void addStudent_ValidData_CreatedSuccessfully() {
        String idStudent = "test";
        String numeStudent = "john";
        int grupa = 934;
        String email = "john_doe@yahoo.com";
        Student student = new Student(idStudent, numeStudent, grupa, email);

        try {
            service.addStudent(student);
        } catch (ValidationException exception) {
            System.out.println(exception);
            assertFalse(true);
        }

        assert(service.findStudent(idStudent) != null);
    }

    @Test
    public void addStudent_EmptyId_ThrowError() {
        String idStudent = "";
        String numeStudent = "john";
        int grupa = 934;
        String email = "john_doe@yahoo.com";
        Student student = new Student(idStudent, numeStudent, grupa, email);

        try {
            service.addStudent(student);
            assert(false);
        } catch (ValidationException exception) {
            System.out.println(exception);
            assert(true);
        }
    }

    @Test
    public void addStudent_NullId_ThrowError() {
        String idStudent = null;
        String numeStudent = "john";
        int grupa = 934;
        String email = "john_doe@yahoo.com";
        Student student = new Student(idStudent, numeStudent, grupa, email);

        try {
            service.addStudent(student);
            assert(true);
        } catch (ValidationException exception) {
            System.out.println(exception);
            assert(true);
        }
    }

    @Test
    public void addStudent_DuplicateId_ThrowError() {
        String idStudent = "test";
        String numeStudent = "john";
        int grupa = 934;
        String email = "john_doe@yahoo.com";
        Student student = new Student(idStudent, numeStudent, grupa, email);

        try {
            Student result = service.addStudent(student);
            assert(result == student);
        } catch (ValidationException exception) {
            System.out.println(exception);
            assert(true);
        }
    }

}
