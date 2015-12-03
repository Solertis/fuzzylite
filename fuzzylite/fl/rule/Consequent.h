/*
 Copyright © 2010-2015 by FuzzyLite Limited.
 All rights reserved.

 This file is part of fuzzylite®.

 fuzzylite® is free software: you can redistribute it and/or modify it under
 the terms of the FuzzyLite License included with the software.

 You should have received a copy of the FuzzyLite License along with 
 fuzzylite®. If not, see <http://www.fuzzylite.com/license/>.

 fuzzylite® is a registered trademark of FuzzyLite Limited.
 */

#ifndef FL_CONSEQUENT_H
#define FL_CONSEQUENT_H

#include "fl/fuzzylite.h"

#include <string>
#include <vector>

namespace fl {
    class Engine;
    class Rule;
    class Proposition;
    class TNorm;

    /**

      The Consequent class is a proposition set that represents and evaluates
      the consequent of a Rule.. The structure of a rule is: `if (antecedent)
      then (consequent)`. The structure of the consequent of a rule is:

      `then variable is [hedge]* term [and variable is [hedge]* term]* [with
      w]?`
      
      where `*`-marked elements may appear zero or more times, elements in
      brackets are optional, elements in parenthesis are compulsory, and
      `?`-marked elements may appear once or not at all.
      
      @author Juan Rada-Vilela, Ph.D.
      @see Antecedent
      @see Rule
      @since 4.0
     */
    class FL_API Consequent {
    protected:
        std::string _text;
        std::vector<Proposition*> _conclusions;

    public:
        Consequent();
        virtual ~Consequent();

        /**
          Sets the text of the consequent
          @param text is the text of the consequent 
         */
        virtual void setText(const std::string& text);
        /**
          Gets the text of the consequent 
          @return the text of the consequent
         */
        virtual std::string getText() const;

        /**
          Provides an immutable vector of the set of propositions that
          represent the Consequent of a Rule

          @return an immutable vector of the set of propositions that represent
          the Consequent of a Rule
         */
        virtual const std::vector<Proposition*>& conclusions() const;

        /**
          Indicates if the consequent is loaded
          @return whether the consequent is loaded
         */
        virtual bool isLoaded();
        /**
          Unloads the consequent
         */
        virtual void unload();
        /**
          Loads the consequent with text given from ::getText(), uses the given
          rule (from which the consequent is part of) to register and retrieve
          the necessary hedges, and uses the engine to identify and retrieve
          references to the input variables and output variables as required
          
          @param rule is the rule from which the consequent is part of
          @param engine is the engine from which the rules are part of
         */
        virtual void load(Rule* rule, const Engine* engine);
        /**
          Loads the consequent with the given text, uses the given rule (from
          which the consequent is part of) to register and retrieve the
          necessary hedges, and uses the engine to identify and retrieve
          references to the input variables and output variables as required
          
          @param consequent is the consequent of the rule in text
          @param rule is the rule from which the consequent is part of
          @param engine is the engine from which the rules are part of
         */
        virtual void load(const std::string& consequent, Rule* rule, const Engine* engine);

        /**
          Modifies the proposition set according to the activation degree
          (computed in the Antecedent of the Rule) and the implication operator
          (given in the RuleBlock)

          @param activationDegree is the activation degree computed in the 
          Antecedent of the Rule
          @param implication is the implication operator configured in the
          RuleBlock
         */
        virtual void modify(scalar activationDegree, const TNorm* implication);

        /**
          Returns a string representation of the Consequent
          @return a string representation of the Consequent
         */
        virtual std::string toString() const;

    private:
        FL_DISABLE_COPY(Consequent)
    };

}

#endif /* FL_CONSEQUENT_H */
