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

  /**
   * [option_definition description]
   * @return [type] [description]
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['hide_if_field_empty'] = array('default' => "");
    $options['hide_if_no_field_empty'] = array('default' => "");
    $options['custom_ex'] = array('default' => 0);
    $options['custom_ex_field'] = array("default" => "");
    $options['custom_ex_value'] = array("default" => "");
    $options['custom_ex_no'] = array('default' => 0);
    $options['custom_ex_no_field'] = array("default" => "");
    $options['custom_ex_no_value'] = array("default" => "");
    return $options;
  }

  /**
   * [options_form description]
   * @param  [type] &$form       [description]
   * @param  [type] &$form_state [description]
   * @return [type]              [description]
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Fieldset to contain logic stuffs.
    $form['advanced_hide_field'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced hide field'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 100,
    );

    // extra fields.
    // $display = $this->view->current_display;
    // $fields = array_keys($this->view->display[$display]->handler->handlers['field']);
    // $fields_key = array_combine($fields, $fields);

    $form['hide_if_field_empty'] = array(
      '#type' => 'textfield',
      '#title' => t("Hide if another field is empty"),
      '#default_value' => $this->options['hide_if_field_empty'],
      '#fieldset' => 'advanced_hide_field',
    );

    $form['hide_if_no_field_empty'] = array(
      '#type' => 'textfield',
      '#title' => t("Hide if another field is NOT empty"),
      '#default_value' => $this->options['hide_if_no_field_empty'],
      '#fieldset' => 'advanced_hide_field',
    );

    // Field is equal to...
    $form['custom_ex'] = array(
      '#type' => 'checkbox',
      '#title' => t("Hide if another field value is equal to"),
      '#weight' => -2,
      '#default_value' => $this->options['custom_ex'],
      '#fieldset' => 'advanced_hide_field',
    );

    $form['custom_ex_field'] = array(
      '#type' => "textfield",
      '#title' => t("Field machine name"),
      '#weight' => -2,
      '#default_value' => $this->options['custom_ex_field'],
      '#fieldset' => 'advanced_hide_field',
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
      '#default_value' => $this->options['custom_ex_value'],
      '#fieldset' => 'advanced_hide_field',
      '#states' => array(
        'visible' => array(
          ':input[name="options[custom_ex]"]' => array('checked' => TRUE),
        ),
      ),
    );

    // Field is NOT equal to...
    $form['custom_ex_no'] = array(
      '#type' => 'checkbox',
      '#title' => t("Hide if another field value is NOT equal to"),
      '#weight' => -2,
      '#default_value' => $this->options['custom_ex_no'],
      '#fieldset' => 'advanced_hide_field',
    );

    $form['custom_ex_no_field'] = array(
      '#type' => "textfield",
      '#title' => t("Field machine name"),
      '#weight' => -2,
      '#default_value' => $this->options['custom_ex_no_field'],
      '#fieldset' => 'advanced_hide_field',
      '#states' => array(
        'visible' => array(
          ':input[name="options[custom_ex_no]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['custom_ex_no_value'] = array(
      '#type' => 'textfield',
      '#title' => t("Field value"),
      '#weight' => -1,
      '#description' => t("Compare this text to the result value for equality."),
      '#default_value' => $this->options['custom_ex_no_value'],
      '#fieldset' => 'advanced_hide_field',
      '#states' => array(
        'visible' => array(
          ':input[name="options[custom_ex_no]"]' => array('checked' => TRUE),
        ),
      ),
    );

  }

  /**
   * [render description]
   * @param  [type] $values [description]
   * @return [type]         [description]
   */
  function advanced_render($values) {
    $options = $this->options;
    $hide = array();

    // Empty check.
    if (isset($options['hide_if_field_empty']) && !empty($options['hide_if_field_empty'])) {
      $keys = explode(",", $options['hide_if_field_empty']);
      foreach ($keys as $index => $field_name) {
        if (!isset($values->{$field_name}) || empty($values->{$field_name})) {
          $hide[] = TRUE;
        }
        else {
          $hide[] = FALSE;
        }
      }
    }

    // NOT empty check.
    if (isset($options['hide_if_no_field_empty']) && !empty($options['hide_if_no_field_empty'])) {
      $keys = explode(",", $options['hide_if_no_field_empty']);
      foreach ($keys as $index => $field_name) {
        if (!isset($values->{$field_name}) || empty($values->{$field_name})) {
          $hide[] = FALSE;
        }
        else {
          $hide[] = TRUE;
        }
      }
    }

    // Is equal to check.
    if (isset($options['custom_ex']) && $options['custom_ex'] === 1) {
      if (!empty($options['custom_ex_field']) && !empty($options['custom_ex_value'])) {
        $field = $options['custom_ex_field'];

        // If field doesnt exist than it can never be equal to something.
        if (!isset($values->{$field})) {
          $hide[] = FALSE;
        }

        if (isset($values->{$field}[0]) && $values->{$field}[0]['raw']['value'] == $options['custom_ex_value']) {
          $hide[] = TRUE;
        }
        else {
          $hide[] = FALSE;
        }

      }
    }

    // Is NOT equal to check.
    if (isset($options['custom_ex_no']) && $options['custom_ex_no'] === 1) {
      if (!empty($options['custom_ex_no_field']) && !empty($options['custom_ex_no_value'])) {
        $field = $options['custom_ex_no_field'];

        // If field doesnt exist than it can never be equal to something.
        if (!isset($values->{$field})) {
          $hide[] = TRUE;
        }

        if (isset($values->{$field}[0]) && $values->{$field}[0]['raw']['value'] !== $options['custom_ex_no_value']) {
          $hide[] = TRUE;
        }
        else {
          $hide[] = FALSE;
        }

      }
    }


    $hide = array_unique($hide);
    if (empty($hide)) {
      return parent::advanced_render($values);
    }

    // Do not hide. Allow parent to render.
    if (count($hide) > 1) {
      $this->last_render = NULL;
      return NULL;
    }

    if (count($hide) == 1 && $hide[0] === TRUE) {
      $this->last_render = NULL;
      return NULL;
    }

    // // Something triggered true. Hide the sucka.
    // $this->last_render = NULL;
    // return NULL;

    return parent::advanced_render($values);
  }


}
