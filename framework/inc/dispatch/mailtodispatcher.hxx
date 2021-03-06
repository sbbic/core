/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_FRAMEWORK_INC_DISPATCH_MAILTODISPATCHER_HXX
#define INCLUDED_FRAMEWORK_INC_DISPATCH_MAILTODISPATCHER_HXX

#include <macros/generic.hxx>
#include <macros/xinterface.hxx>
#include <macros/xtypeprovider.hxx>
#include <macros/xserviceinfo.hxx>
#include <general.h>
#include <stdtypes.h>

#include <com/sun/star/lang/XTypeProvider.hpp>
#include <com/sun/star/frame/XNotifyingDispatch.hpp>
#include <com/sun/star/frame/XDispatch.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/util/URL.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/frame/XStatusListener.hpp>

#include <cppuhelper/implbase.hxx>

namespace framework{

/**
    @short          protocol handler for "mailto:" URLs
    @descr          It's a special dispatch object which is used registered for "mailto:*" URLs and
                    will be automatically used from the framework dispatch mechanism if such URL occurred.

    @base           OWeakObject
                        provides XWeak and ref count mechanism

    @devstatus      ready to use
*/
class MailToDispatcher : public  ::cppu::WeakImplHelper<
                                     css::lang::XServiceInfo,
                                     css::frame::XDispatchProvider,
                                     css::frame::XNotifyingDispatch> // => XDispatch
{
    /* member */
    private:

        /// reference to global uno service manager which had created us
        css::uno::Reference< css::uno::XComponentContext > m_xContext;

    /* interface */
    public:

        // ctor/dtor
                 MailToDispatcher( const css::uno::Reference< css::uno::XComponentContext >& rxContext );
        virtual ~MailToDispatcher(                                                                     );

        // XInterface, XTypeProvider, XServiceInfo
        DECLARE_XSERVICEINFO

        // XDispatchProvider
        virtual css::uno::Reference< css::frame::XDispatch > SAL_CALL                       queryDispatch  ( const css::util::URL&                                       aURL        ,
                                                                                                             const OUString&                                      sTarget     ,
                                                                                                                   sal_Int32                                             nFlags      ) throw( css::uno::RuntimeException, std::exception ) SAL_OVERRIDE;
        virtual css::uno::Sequence< css::uno::Reference< css::frame::XDispatch > > SAL_CALL queryDispatches( const css::uno::Sequence< css::frame::DispatchDescriptor >& lDescriptor ) throw( css::uno::RuntimeException, std::exception ) SAL_OVERRIDE;

        // XNotifyingDispatch
        virtual void SAL_CALL dispatchWithNotification( const css::util::URL&                                             aURL      ,
                                                        const css::uno::Sequence< css::beans::PropertyValue >&            lArguments,
                                                        const css::uno::Reference< css::frame::XDispatchResultListener >& xListener ) throw( css::uno::RuntimeException, std::exception ) SAL_OVERRIDE;

        // XDispatch
        virtual void SAL_CALL dispatch            ( const css::util::URL&                                     aURL       ,
                                                    const css::uno::Sequence< css::beans::PropertyValue >&    lArguments ) throw( css::uno::RuntimeException, std::exception ) SAL_OVERRIDE;
        virtual void SAL_CALL addStatusListener   ( const css::uno::Reference< css::frame::XStatusListener >& xListener  ,
                                                    const css::util::URL&                                     aURL       ) throw( css::uno::RuntimeException, std::exception ) SAL_OVERRIDE;
        virtual void SAL_CALL removeStatusListener( const css::uno::Reference< css::frame::XStatusListener >& xListener  ,
                                                    const css::util::URL&                                     aURL       ) throw( css::uno::RuntimeException, std::exception ) SAL_OVERRIDE;

    /* internal */
    private:

        bool implts_dispatch( const css::util::URL&                                  aURL       ,
                                  const css::uno::Sequence< css::beans::PropertyValue >& lArguments ) throw( css::uno::RuntimeException );

};      //  class MailToDispatcher

}       //  namespace framework

#endif // INCLUDED_FRAMEWORK_INC_DISPATCH_MAILTODISPATCHER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
