<?php

/**
 * @file
 * Definition of views_handler_field_custom.
 */

/**
 * A handler to provide a field that is completely custom by the administrator.
 *
 * @ingroup views_field_handlers
 */
class caw_helper_views_handler_field_custom extends views_handler_field_custom {


  function option_definition() {
    $options = parent::option_definition();
    $options['custom_ex'] = 0;
    $options['custom_ex_field'] = "";
    $options['custom_ex_value'] = "";
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['custom_ex'] = array(
      '#type' => 'checkbox',
      '#title' => t("Exclude if another field value is equal to"),
      '#weight' => -1,
    );

    $form['custom_ex_field'] = array(
      '#type' => "textfield",
      '#title' => t("Field machine name"),
      '#weight' => -1,
      '#states' => array(
        'visible' => array(
          ':input[name="options[custom_ex]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['custom_ex_value'] = array(
      '#type' => 'textfield',
      '#title' => t("Field value"),
      '#weight' => -1,
      '#description' => t("Compare this text to the result value for equality."),
      '#states' => array(
        'visible' => array(
          'input[name="options[custom_ex]"]' => array('checked' => TRUE),
        ),
      ),
    );

  }

  function render($values) {
    // Return the text, so the code never thinks the value is empty.
    return "<h1>HELLO WORLD</h1>" . $this->options['alter']['text'];
  }
}
