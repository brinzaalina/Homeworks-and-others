import repository.Repository;
import service.Service;
import view.View;

public class Main {
    public static void main(String[] args) {
        // create repo, service, view and run app
        Repository repository = new Repository();
        Service service = new Service(repository);
        View view = new View(service);
        view.run();
    }
}
