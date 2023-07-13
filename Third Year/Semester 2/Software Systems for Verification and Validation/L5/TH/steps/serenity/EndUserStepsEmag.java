package org.example.steps.serenity;

import net.thucydides.core.annotations.Step;
import org.example.pages.EmagPage;

public class EndUserStepsEmag {
    EmagPage emagPage;

    @Step
    public void is_the_home_page() {
        emagPage.open();
    }

    @Step
    public void filter_products(String filter) {
        assert emagPage.filter_results(filter);
    }

    @Step
    public void should_see_products(String productName) {
        assert emagPage.get_products(productName).size() > 0;
    }

    @Step
    public void enters(String keyword) {
        emagPage.enter_keywords(keyword);
    }

    @Step
    public void starts_search() {
        emagPage.lookup_terms();
    }

    @Step
    public void looks_for(String term) {
        enters(term);
        starts_search();
    }
}
